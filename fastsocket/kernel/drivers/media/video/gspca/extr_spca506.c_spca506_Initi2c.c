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
struct gspca_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7113_I2C_BASE_WRITE ; 
 int /*<<< orphan*/  reg_w (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void spca506_Initi2c(struct gspca_dev *gspca_dev)
{
	reg_w(gspca_dev->dev, 0x07, SAA7113_I2C_BASE_WRITE, 0x0004);
}