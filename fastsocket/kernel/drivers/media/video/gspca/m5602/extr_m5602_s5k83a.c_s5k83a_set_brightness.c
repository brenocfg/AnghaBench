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
typedef  void* u8 ;
struct sd {struct s5k83a_priv* sensor_priv; } ;
struct s5k83a_priv {void** settings; } ;
struct gspca_dev {int dummy; } ;
typedef  void* __s32 ;

/* Variables and functions */
 size_t BRIGHTNESS_IDX ; 
 int /*<<< orphan*/  S5K83A_BRIGHTNESS ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,void**,int) ; 

__attribute__((used)) static int s5k83a_set_brightness(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u8 data[1];
	struct sd *sd = (struct sd *) gspca_dev;
	struct s5k83a_priv *sens_priv = sd->sensor_priv;

	sens_priv->settings[BRIGHTNESS_IDX] = val;
	data[0] = val;
	err = m5602_write_sensor(sd, S5K83A_BRIGHTNESS, data, 1);
	return err;
}