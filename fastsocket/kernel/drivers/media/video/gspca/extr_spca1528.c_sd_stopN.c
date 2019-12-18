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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  wait_status_0 (struct gspca_dev*) ; 
 int /*<<< orphan*/  wait_status_1 (struct gspca_dev*) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	/* stop the capture */
	wait_status_0(gspca_dev);
	reg_w(gspca_dev, 0x31, 0x0000, 0x0000);
	wait_status_1(gspca_dev);
	wait_status_0(gspca_dev);
}