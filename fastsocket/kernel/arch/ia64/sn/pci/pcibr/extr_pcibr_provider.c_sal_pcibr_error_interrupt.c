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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int bs_persist_segment; scalar_t__ bs_persist_busnum; } ;
struct pcibus_info {TYPE_1__ pbi_buscommon; } ;
struct ia64_sal_retval {scalar_t__ v0; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAL_CALL_NOLOCK (struct ia64_sal_retval,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SN_SAL_IOIF_ERROR_INTERRUPT ; 

__attribute__((used)) static int sal_pcibr_error_interrupt(struct pcibus_info *soft)
{
	struct ia64_sal_retval ret_stuff;
	u64 busnum;
	int segment;
	ret_stuff.status = 0;
	ret_stuff.v0 = 0;

	segment = soft->pbi_buscommon.bs_persist_segment;
	busnum = soft->pbi_buscommon.bs_persist_busnum;
	SAL_CALL_NOLOCK(ret_stuff,
			(u64) SN_SAL_IOIF_ERROR_INTERRUPT,
			(u64) segment, (u64) busnum, 0, 0, 0, 0, 0);

	return (int)ret_stuff.v0;
}