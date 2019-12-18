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
struct sd {int /*<<< orphan*/ * sensor_priv; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 size_t AUTO_WHITE_BALANCE_IDX ; 

__attribute__((used)) static int ov9650_get_auto_white_balance(struct gspca_dev *gspca_dev,
					 __s32 *val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;

	*val = sensor_settings[AUTO_WHITE_BALANCE_IDX];
	return 0;
}