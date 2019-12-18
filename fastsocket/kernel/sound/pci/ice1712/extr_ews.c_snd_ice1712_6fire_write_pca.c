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
struct snd_ice1712 {int /*<<< orphan*/  i2c; struct ews_spec* spec; } ;
struct ews_spec {int /*<<< orphan*/ * i2cdevs; } ;

/* Variables and functions */
 int EIO ; 
 size_t EWS_I2C_6FIRE ; 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int snd_i2c_sendbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ice1712_6fire_write_pca(struct snd_ice1712 *ice, unsigned char reg, unsigned char data)
{
	unsigned char bytes[2];
	struct ews_spec *spec = ice->spec;

	snd_i2c_lock(ice->i2c);
	bytes[0] = reg;
	bytes[1] = data;
	if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_6FIRE], bytes, 2) != 2) {
		snd_i2c_unlock(ice->i2c);
		return -EIO;
	}
	snd_i2c_unlock(ice->i2c);
	return 0;
}