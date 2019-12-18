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
typedef  int u8 ;
struct w83791d_data {int /*<<< orphan*/  vrm; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83791D_REG_BEEP_CONFIG ; 
 int /*<<< orphan*/ * W83791D_REG_BEEP_CTRL ; 
 int /*<<< orphan*/  W83791D_REG_CONFIG ; 
 int /*<<< orphan*/  W83791D_REG_TEMP2_CONFIG ; 
 int /*<<< orphan*/  W83791D_REG_TEMP3_CONFIG ; 
 struct w83791d_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ init ; 
 scalar_t__ reset ; 
 int /*<<< orphan*/  vid_which_vrm () ; 
 int w83791d_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83791d_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w83791d_init_client(struct i2c_client *client)
{
	struct w83791d_data *data = i2c_get_clientdata(client);
	u8 tmp;
	u8 old_beep;

	/* The difference between reset and init is that reset
	   does a hard reset of the chip via index 0x40, bit 7,
	   but init simply forces certain registers to have "sane"
	   values. The hope is that the BIOS has done the right
	   thing (which is why the default is reset=0, init=0),
	   but if not, reset is the hard hammer and init
	   is the soft mallet both of which are trying to whack
	   things into place...
	   NOTE: The data sheet makes a distinction between
	   "power on defaults" and "reset by MR". As far as I can tell,
	   the hard reset puts everything into a power-on state so I'm
	   not sure what "reset by MR" means or how it can happen.
	   */
	if (reset || init) {
		/* keep some BIOS settings when we... */
		old_beep = w83791d_read(client, W83791D_REG_BEEP_CONFIG);

		if (reset) {
			/* ... reset the chip and ... */
			w83791d_write(client, W83791D_REG_CONFIG, 0x80);
		}

		/* ... disable power-on abnormal beep */
		w83791d_write(client, W83791D_REG_BEEP_CONFIG, old_beep | 0x80);

		/* disable the global beep (not done by hard reset) */
		tmp = w83791d_read(client, W83791D_REG_BEEP_CTRL[1]);
		w83791d_write(client, W83791D_REG_BEEP_CTRL[1], tmp & 0xef);

		if (init) {
			/* Make sure monitoring is turned on for add-ons */
			tmp = w83791d_read(client, W83791D_REG_TEMP2_CONFIG);
			if (tmp & 1) {
				w83791d_write(client, W83791D_REG_TEMP2_CONFIG,
					tmp & 0xfe);
			}

			tmp = w83791d_read(client, W83791D_REG_TEMP3_CONFIG);
			if (tmp & 1) {
				w83791d_write(client, W83791D_REG_TEMP3_CONFIG,
					tmp & 0xfe);
			}

			/* Start monitoring */
			tmp = w83791d_read(client, W83791D_REG_CONFIG) & 0xf7;
			w83791d_write(client, W83791D_REG_CONFIG, tmp | 0x01);
		}
	}

	data->vrm = vid_which_vrm();
}