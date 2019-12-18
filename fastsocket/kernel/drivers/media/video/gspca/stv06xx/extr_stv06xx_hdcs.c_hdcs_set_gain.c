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
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_V4L2 ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int hdcs_set_gains (struct sd*,int) ; 

__attribute__((used)) static int hdcs_set_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	PDEBUG(D_V4L2, "Writing gain %d", val);
	return hdcs_set_gains((struct sd *) gspca_dev,
			       val & 0xff);
}