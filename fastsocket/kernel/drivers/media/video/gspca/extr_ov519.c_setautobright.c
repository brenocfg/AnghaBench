#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {TYPE_1__* ctrls; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 size_t AUTOBRIGHT ; 
 int /*<<< orphan*/  i2c_w_mask (struct sd*,int,int,int) ; 

__attribute__((used)) static void setautobright(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	i2c_w_mask(sd, 0x2d, sd->ctrls[AUTOBRIGHT].val ? 0x10 : 0x00, 0x10);
}