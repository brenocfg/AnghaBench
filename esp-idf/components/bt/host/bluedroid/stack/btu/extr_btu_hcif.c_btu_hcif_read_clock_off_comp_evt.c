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
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  HCID_GET_HANDLE (int /*<<< orphan*/ ) ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  btm_process_clk_off_comp_evt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_update_clock_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_read_clock_off_comp_evt (UINT8 *p)
{
    UINT8       status;
    UINT16      handle;
    UINT16      clock_offset;

    STREAM_TO_UINT8  (status, p);

    /* If failed to get clock offset just drop the result */
    if (status != HCI_SUCCESS) {
        return;
    }

    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT16 (clock_offset, p);

    handle = HCID_GET_HANDLE (handle);

    btm_process_clk_off_comp_evt (handle, clock_offset);
    btm_sec_update_clock_offset (handle, clock_offset);
}