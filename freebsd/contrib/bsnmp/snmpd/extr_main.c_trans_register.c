#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct transport_def {char* name; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int* subs; void* len; } ;
struct transport {int /*<<< orphan*/  table; int /*<<< orphan*/  or_index; TYPE_1__ index; struct transport_def const* vtab; } ;
typedef  int /*<<< orphan*/  or_descr ;

/* Variables and functions */
 int /*<<< orphan*/ * FIND_OBJECT_OID (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSERT_OBJECT_OID (struct transport*,int /*<<< orphan*/ *) ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct transport*) ; 
 struct transport* malloc (int) ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  transport_list ; 

int
trans_register(const struct transport_def *def, struct transport **pp)
{
	u_int i;
	char or_descr[256];

	if ((*pp = malloc(sizeof(**pp))) == NULL)
		return (SNMP_ERR_GENERR);

	/* construct index */
	(*pp)->index.len = strlen(def->name) + 1;
	(*pp)->index.subs[0] = strlen(def->name);
	for (i = 0; i < (*pp)->index.subs[0]; i++)
		(*pp)->index.subs[i + 1] = def->name[i];

	(*pp)->vtab = def;

	if (FIND_OBJECT_OID(&transport_list, &(*pp)->index, 0) != NULL) {
		free(*pp);
		return (SNMP_ERR_INCONS_VALUE);
	}

	/* register module */
	snprintf(or_descr, sizeof(or_descr), "%s transport mapping", def->name);
	if (((*pp)->or_index = or_register(&def->id, or_descr, NULL)) == 0) {
		free(*pp);
		return (SNMP_ERR_GENERR);
	}

	INSERT_OBJECT_OID((*pp), &transport_list);

	TAILQ_INIT(&(*pp)->table);

	return (SNMP_ERR_NOERROR);
}