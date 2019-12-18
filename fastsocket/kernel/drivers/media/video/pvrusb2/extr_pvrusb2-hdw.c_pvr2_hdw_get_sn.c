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
struct pvr2_hdw {unsigned long serial_number; } ;

/* Variables and functions */

unsigned long pvr2_hdw_get_sn(struct pvr2_hdw *hdw)
{
	return hdw->serial_number;
}