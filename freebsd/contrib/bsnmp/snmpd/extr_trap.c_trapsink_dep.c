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
struct trapsink_dep {int set; int rb; int /*<<< orphan*/  status; } ;
struct trapsink {int dummy; } ;
struct snmp_dependency {int /*<<< orphan*/  idx; } ;
struct snmp_context {int /*<<< orphan*/  code; } ;
typedef  enum snmp_depop { ____Placeholder_snmp_depop } snmp_depop ;

/* Variables and functions */
 struct trapsink* FIND_OBJECT_OID (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  SNMP_DEPOP_COMMIT 130 
#define  SNMP_DEPOP_FINISH 129 
#define  SNMP_DEPOP_ROLLBACK 128 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  SNMP_RET_OK ; 
 int TDEP_CREATE ; 
 int TDEP_DESTROY ; 
 int TDEP_MODIFY ; 
 int TDEP_STATUS ; 
 int /*<<< orphan*/  abort () ; 
 int trapsink_create (struct trapsink_dep*) ; 
 int trapsink_destroy (struct snmp_context*,struct trapsink*,struct trapsink_dep*) ; 
 int /*<<< orphan*/  trapsink_free (struct trapsink*) ; 
 int /*<<< orphan*/  trapsink_list ; 
 int trapsink_modify (struct trapsink*,struct trapsink_dep*) ; 
 int trapsink_undestroy (struct trapsink*,struct trapsink_dep*) ; 
 int trapsink_unmodify (struct trapsink*,struct trapsink_dep*) ; 

__attribute__((used)) static int
trapsink_dep(struct snmp_context *ctx, struct snmp_dependency *dep,
    enum snmp_depop op)
{
	struct trapsink_dep *tdep = (struct trapsink_dep *)dep;
	struct trapsink *t;

	t = FIND_OBJECT_OID(&trapsink_list, &dep->idx, 0);

	switch (op) {

	  case SNMP_DEPOP_COMMIT:
		if (tdep->set & TDEP_STATUS) {
			switch (tdep->status) {

			  case 1:
			  case 2:
				if (t == NULL)
					return (SNMP_ERR_INCONS_VALUE);
				return (trapsink_modify(t, tdep));

			  case 4:
			  case 5:
				if (t != NULL)
					return (SNMP_ERR_INCONS_VALUE);
				return (trapsink_create(tdep));

			  case 6:
				if (t == NULL)
					return (SNMP_ERR_NOERROR);
				return (trapsink_destroy(ctx, t, tdep));
			}
		} else if (tdep->set != 0)
			return (trapsink_modify(t, tdep));

		return (SNMP_ERR_NOERROR);

	  case SNMP_DEPOP_ROLLBACK:
		if (tdep->rb & TDEP_CREATE) {
			trapsink_free(t);
			return (SNMP_ERR_NOERROR);
		}
		if (tdep->rb & TDEP_MODIFY)
			return (trapsink_unmodify(t, tdep));
		if(tdep->rb & TDEP_DESTROY)
			return (trapsink_undestroy(t, tdep));
		return (SNMP_ERR_NOERROR);

	  case SNMP_DEPOP_FINISH:
		if ((tdep->rb & TDEP_DESTROY) && t != NULL &&
		    ctx->code == SNMP_RET_OK)
			trapsink_free(t);
		return (SNMP_ERR_NOERROR);
	}
	abort();
}