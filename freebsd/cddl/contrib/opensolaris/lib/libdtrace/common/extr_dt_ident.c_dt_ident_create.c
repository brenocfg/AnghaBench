#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* ushort_t ;
typedef  int /*<<< orphan*/  ulong_t ;
typedef  void* uint_t ;
typedef  int /*<<< orphan*/  dtrace_attribute_t ;
typedef  int /*<<< orphan*/  dt_idops_t ;
struct TYPE_4__ {char* di_name; int /*<<< orphan*/  di_lineno; int /*<<< orphan*/  di_gen; int /*<<< orphan*/ * di_next; int /*<<< orphan*/  di_type; int /*<<< orphan*/ * di_ctfp; int /*<<< orphan*/ * di_data; void* di_iarg; int /*<<< orphan*/  const* di_ops; void* di_vers; int /*<<< orphan*/  di_attr; void* di_id; void* di_flags; void* di_kind; } ;
typedef  TYPE_1__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* malloc (int) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  yylineno ; 

dt_ident_t *
dt_ident_create(const char *name, ushort_t kind, ushort_t flags, uint_t id,
    dtrace_attribute_t attr, uint_t vers,
    const dt_idops_t *ops, void *iarg, ulong_t gen)
{
	dt_ident_t *idp;
	char *s = NULL;

	if ((name != NULL && (s = strdup(name)) == NULL) ||
	    (idp = malloc(sizeof (dt_ident_t))) == NULL) {
		free(s);
		return (NULL);
	}

	idp->di_name = s;
	idp->di_kind = kind;
	idp->di_flags = flags;
	idp->di_id = id;
	idp->di_attr = attr;
	idp->di_vers = vers;
	idp->di_ops = ops;
	idp->di_iarg = iarg;
	idp->di_data = NULL;
	idp->di_ctfp = NULL;
	idp->di_type = CTF_ERR;
	idp->di_next = NULL;
	idp->di_gen = gen;
	idp->di_lineno = yylineno;

	return (idp);
}