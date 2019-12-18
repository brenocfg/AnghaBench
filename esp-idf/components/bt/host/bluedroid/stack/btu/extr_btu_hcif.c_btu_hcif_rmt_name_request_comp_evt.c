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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BD_ADDR_LEN ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_process_remote_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_rmt_name_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_rmt_name_request_comp_evt (UINT8 *p, UINT16 evt_len)
{
    UINT8   status;
    BD_ADDR bd_addr;

    STREAM_TO_UINT8 (status, p);
    STREAM_TO_BDADDR (bd_addr, p);

    evt_len -= (1 + BD_ADDR_LEN);

    btm_process_remote_name (bd_addr, p, evt_len, status);
#if (SMP_INCLUDED == TRUE)
    btm_sec_rmt_name_request_complete (bd_addr, p, status);
#endif  ///SMP_INCLUDED == TRUE
}