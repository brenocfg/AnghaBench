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
struct sd {struct s5k83a_priv* sensor_priv; } ;
struct s5k83a_priv {int /*<<< orphan*/ * settings; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 size_t EXPOSURE_IDX ; 

__attribute__((used)) static int s5k83a_get_exposure(struct gspca_dev *gspca_dev, __s32 *val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct s5k83a_priv *sens_priv = sd->sensor_priv;

	*val = sens_priv->settings[EXPOSURE_IDX];
	return 0;
}