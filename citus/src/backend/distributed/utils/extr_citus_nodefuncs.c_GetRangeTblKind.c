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
struct TYPE_4__ {int rtekind; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  int /*<<< orphan*/  CitusRTEKind ;

/* Variables and functions */
 int /*<<< orphan*/  CITUS_RTE_RELATION ; 
 int /*<<< orphan*/  ExtractRangeTblExtraData (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  RTE_CTE 136 
#define  RTE_FUNCTION 135 
#define  RTE_JOIN 134 
#define  RTE_NAMEDTUPLESTORE 133 
#define  RTE_RELATION 132 
#define  RTE_RESULT 131 
#define  RTE_SUBQUERY 130 
#define  RTE_TABLEFUNC 129 
#define  RTE_VALUES 128 

CitusRTEKind
GetRangeTblKind(RangeTblEntry *rte)
{
	CitusRTEKind rteKind = CITUS_RTE_RELATION /* invalid */;

	switch (rte->rtekind)
	{
		/* directly rtekind if it's not possibly an extended RTE */
		case RTE_TABLEFUNC:
		case RTE_NAMEDTUPLESTORE:
		case RTE_RELATION:
		case RTE_SUBQUERY:
		case RTE_JOIN:
		case RTE_VALUES:
		case RTE_CTE:
#if PG_VERSION_NUM >= 120000
		case RTE_RESULT:
#endif
			{
				rteKind = (CitusRTEKind) rte->rtekind;
				break;
			}

		case RTE_FUNCTION:
		{
			/*
			 * Extract extra data - correct even if a plain RTE_FUNCTION, not
			 * an extended one, ExtractRangeTblExtraData handles that case
			 * transparently.
			 */
			ExtractRangeTblExtraData(rte, &rteKind, NULL, NULL, NULL);
			break;
		}
	}

	return rteKind;
}