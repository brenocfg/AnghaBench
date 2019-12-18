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
struct gspca_dev {int ctrl_inac; } ;

/* Variables and functions */
 int ILLUM_BOT ; 
 int ILLUM_TOP ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	gspca_dev->ctrl_inac = (1 << ILLUM_TOP) | (1 << ILLUM_BOT);
	return 0;
}