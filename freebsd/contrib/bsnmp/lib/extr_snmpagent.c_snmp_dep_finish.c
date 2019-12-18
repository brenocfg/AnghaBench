#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snmp_context {int /*<<< orphan*/ * dep; } ;
struct depend {int /*<<< orphan*/  (* func ) (struct snmp_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dep; } ;
struct context {int /*<<< orphan*/  dlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_DEPOP_FINISH ; 
 struct depend* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct depend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct depend*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  stub1 (struct snmp_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
snmp_dep_finish(struct snmp_context *ctx)
{
	struct context *context = (struct context *)ctx;
	struct depend *d;

	while ((d = TAILQ_FIRST(&context->dlist)) != NULL) {
		ctx->dep = &d->dep;
		(void)d->func(ctx, ctx->dep, SNMP_DEPOP_FINISH);
		TAILQ_REMOVE(&context->dlist, d, link);
		free(d);
	}
}