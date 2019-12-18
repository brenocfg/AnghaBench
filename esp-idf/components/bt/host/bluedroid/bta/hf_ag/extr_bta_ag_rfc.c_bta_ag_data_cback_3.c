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
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int bta_ag_data_cback (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 

int bta_ag_data_cback_3(UINT16 port_handle, void *p_data, UINT16 len)
{
    return bta_ag_data_cback(port_handle, p_data, len, 3);
}