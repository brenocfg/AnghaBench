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
struct sd {int /*<<< orphan*/  exposure; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int EXPO_CHANGE ; 
 int LATENT_CHANGE ; 
 int /*<<< orphan*/  R00_PART_CONTROL ; 
 int /*<<< orphan*/  R1C_AD_EXPOSE_TIMEL ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w2 (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_w2(gspca_dev, R1C_AD_EXPOSE_TIMEL, sd->exposure);
	reg_w1(gspca_dev, R00_PART_CONTROL, LATENT_CHANGE | EXPO_CHANGE);
						/* 0x84 */
}