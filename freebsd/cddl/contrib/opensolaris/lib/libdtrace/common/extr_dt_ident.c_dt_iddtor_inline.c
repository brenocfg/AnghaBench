#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* din_argv; int /*<<< orphan*/ * din_hash; int /*<<< orphan*/  din_list; } ;
typedef  TYPE_1__ dt_idnode_t ;
struct TYPE_8__ {scalar_t__ di_kind; TYPE_1__* di_iarg; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 scalar_t__ DT_IDENT_ARRAY ; 
 int /*<<< orphan*/  dt_iddtor_free (TYPE_2__*) ; 
 int /*<<< orphan*/  dt_iddtor_sign (TYPE_2__*) ; 
 int /*<<< orphan*/  dt_idhash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_node_link_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
dt_iddtor_inline(dt_ident_t *idp)
{
	dt_idnode_t *inp = idp->di_iarg;

	if (inp != NULL) {
		dt_node_link_free(&inp->din_list);

		if (inp->din_hash != NULL)
			dt_idhash_destroy(inp->din_hash);

		free(inp->din_argv);
		free(inp);
	}

	if (idp->di_kind == DT_IDENT_ARRAY)
		dt_iddtor_sign(idp);
	else
		dt_iddtor_free(idp);
}