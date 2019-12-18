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
struct tw9910_priv {TYPE_1__* info; } ;
struct soc_camera_link {int dummy; } ;
struct soc_camera_device {int dummy; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {unsigned long buswidth; } ;

/* Variables and functions */
 unsigned long SOCAM_DATA_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_LOW ; 
 unsigned long SOCAM_MASTER ; 
 unsigned long SOCAM_PCLK_SAMPLE_RISING ; 
 unsigned long SOCAM_VSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_VSYNC_ACTIVE_LOW ; 
 unsigned long soc_camera_apply_sensor_flags (struct soc_camera_link*,unsigned long) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_soc_camera_control (struct soc_camera_device*) ; 
 struct soc_camera_link* to_soc_camera_link (struct soc_camera_device*) ; 
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 

__attribute__((used)) static unsigned long tw9910_query_bus_param(struct soc_camera_device *icd)
{
	struct i2c_client *client = to_i2c_client(to_soc_camera_control(icd));
	struct tw9910_priv *priv = to_tw9910(client);
	struct soc_camera_link *icl = to_soc_camera_link(icd);
	unsigned long flags = SOCAM_PCLK_SAMPLE_RISING | SOCAM_MASTER |
		SOCAM_VSYNC_ACTIVE_HIGH | SOCAM_HSYNC_ACTIVE_HIGH |
		SOCAM_VSYNC_ACTIVE_LOW  | SOCAM_HSYNC_ACTIVE_LOW  |
		SOCAM_DATA_ACTIVE_HIGH | priv->info->buswidth;

	return soc_camera_apply_sensor_flags(icl, flags);
}