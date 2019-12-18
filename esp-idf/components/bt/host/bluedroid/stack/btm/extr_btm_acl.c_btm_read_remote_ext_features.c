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

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_rmt_ext_features (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_read_remote_ext_features (UINT16 handle, UINT8 page_number)
{
    BTM_TRACE_DEBUG("btm_read_remote_ext_features() handle: %d page: %d\n", handle, page_number);

    btsnd_hcic_rmt_ext_features(handle, page_number);
}