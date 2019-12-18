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
struct sd {int /*<<< orphan*/  blue; int /*<<< orphan*/  red; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_redblue(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	reg_w1(gspca_dev, 0x118c, sd->red);
	reg_w1(gspca_dev, 0x118f, sd->blue);
	return 0;
}