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
struct vc_data {int vc_cols; int vc_rows; int vc_can_do_color; } ;

/* Variables and functions */
 int newport_xsize ; 
 int newport_ysize ; 

__attribute__((used)) static void newport_init(struct vc_data *vc, int init)
{
	vc->vc_cols = newport_xsize / 8;
	vc->vc_rows = newport_ysize / 16;
	vc->vc_can_do_color = 1;
}