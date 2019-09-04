#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  CedarGetCurrentTcpQueueSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CedarGetFifoBudgetConsuming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CedarGetQueueBudgetConsuming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  ToStr3 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT SiDebugProcGetCurrentTcpSendQueueLength(SERVER *s, char *in_str, char *ret_str, UINT ret_str_size)
{
	char tmp1[64], tmp2[64], tmp3[64];
	// Validate arguments
	if (s == NULL || in_str == NULL || ret_str == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	ToStr3(tmp1, 0, CedarGetCurrentTcpQueueSize(s->Cedar));
	ToStr3(tmp2, 0, CedarGetQueueBudgetConsuming(s->Cedar));
	ToStr3(tmp3, 0, CedarGetFifoBudgetConsuming(s->Cedar));

	Format(ret_str, 0, 
		"CurrentTcpQueueSize  = %s\n"
		"QueueBudgetConsuming = %s\n"
		"FifoBudgetConsuming  = %s\n",
		tmp1, tmp2, tmp3);

	return ERR_NO_ERROR;
}