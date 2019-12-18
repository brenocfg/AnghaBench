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
typedef  int /*<<< orphan*/  tBTA_OOB_DATA ;
typedef  int /*<<< orphan*/  tBTA_IO_CAP ;
typedef  int /*<<< orphan*/  tBTA_AUTH_REQ ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTIF_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  btif_dm_proc_io_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_co_io_rsp(BD_ADDR bd_addr, tBTA_IO_CAP io_cap,
                      tBTA_OOB_DATA oob_data, tBTA_AUTH_REQ auth_req)
{
#if (defined(BTIF_INCLUDED) && BTIF_INCLUDED == TRUE)
    btif_dm_proc_io_rsp(bd_addr, io_cap, oob_data, auth_req);
#else
    BTIF_TRACE_DEBUG("bta_dm_co_io_rsp: func not ported\n");
#endif /* #if (defined(BTIF_INCLUDED) && BTIF_INCLUDED == TRUE) */
}