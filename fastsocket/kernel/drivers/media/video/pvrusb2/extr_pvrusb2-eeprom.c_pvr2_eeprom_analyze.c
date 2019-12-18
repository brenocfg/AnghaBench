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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tvdata ;
struct tveeprom {int /*<<< orphan*/  tuner_formats; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  tuner_type; int /*<<< orphan*/  rev_str; int /*<<< orphan*/  revision; int /*<<< orphan*/  model; int /*<<< orphan*/  audio_processor; int /*<<< orphan*/  has_radio; } ;
struct pvr2_hdw {int tuner_updated; int /*<<< orphan*/  std_mask_eeprom; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  tuner_type; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  eeprom_addr; } ;
struct i2c_client {int /*<<< orphan*/ * adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tveeprom*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pvr2_eeprom_fetch (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  trace_eeprom (char*,...) ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (struct i2c_client*,struct tveeprom*,int /*<<< orphan*/ *) ; 

int pvr2_eeprom_analyze(struct pvr2_hdw *hdw)
{
	u8 *eeprom;
	struct tveeprom tvdata;

	memset(&tvdata,0,sizeof(tvdata));

	eeprom = pvr2_eeprom_fetch(hdw);
	if (!eeprom) return -EINVAL;

	{
		struct i2c_client fake_client;
		/* Newer version expects a useless client interface */
		fake_client.addr = hdw->eeprom_addr;
		fake_client.adapter = &hdw->i2c_adap;
		tveeprom_hauppauge_analog(&fake_client,&tvdata,eeprom);
	}

	trace_eeprom("eeprom assumed v4l tveeprom module");
	trace_eeprom("eeprom direct call results:");
	trace_eeprom("has_radio=%d",tvdata.has_radio);
	trace_eeprom("tuner_type=%d",tvdata.tuner_type);
	trace_eeprom("tuner_formats=0x%x",tvdata.tuner_formats);
	trace_eeprom("audio_processor=%d",tvdata.audio_processor);
	trace_eeprom("model=%d",tvdata.model);
	trace_eeprom("revision=%d",tvdata.revision);
	trace_eeprom("serial_number=%d",tvdata.serial_number);
	trace_eeprom("rev_str=%s",tvdata.rev_str);
	hdw->tuner_type = tvdata.tuner_type;
	hdw->tuner_updated = !0;
	hdw->serial_number = tvdata.serial_number;
	hdw->std_mask_eeprom = tvdata.tuner_formats;

	kfree(eeprom);

	return 0;
}