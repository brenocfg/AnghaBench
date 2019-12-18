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
struct sd {size_t gamma; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * gamma_table ; 
 int /*<<< orphan*/  reg_w_ixbuf (struct gspca_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setgamma(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	PDEBUG(D_CONF, "Gamma: %d", sd->gamma);
	reg_w_ixbuf(gspca_dev, 0x90,
		gamma_table[sd->gamma], sizeof gamma_table[0]);
}