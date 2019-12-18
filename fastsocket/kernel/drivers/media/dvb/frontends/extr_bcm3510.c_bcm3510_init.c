#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dvb_frontend {struct bcm3510_state* demodulator_priv; } ;
struct bcm3510_state {int dummy; } ;
struct bcm3510_hab_cmd_set_agc {int SEL; } ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_4__ {int JDEC; } ;
struct TYPE_5__ {TYPE_1__ JDEC_ca; int /*<<< orphan*/  raw; } ;
typedef  TYPE_2__ bcm3510_register_value ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_AUTO_PARAM ; 
 int ENODEV ; 
#define  JDEC_EEPROM_LOAD_WAIT 129 
#define  JDEC_WAIT_AT_RAM 128 
 int /*<<< orphan*/  MSGID_SET_RF_AGC_SEL ; 
 int /*<<< orphan*/  bcm3510_check_firmware_version (struct bcm3510_state*) ; 
 int /*<<< orphan*/  bcm3510_do_hab_cmd (struct bcm3510_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bcm3510_init_cold (struct bcm3510_state*) ; 
 int bcm3510_readB (struct bcm3510_state*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 
 int /*<<< orphan*/  memset (struct bcm3510_hab_cmd_set_agc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm3510_init(struct dvb_frontend* fe)
{
	struct bcm3510_state* st = fe->demodulator_priv;
	bcm3510_register_value j;
	struct bcm3510_hab_cmd_set_agc c;
	int ret;

	if ((ret = bcm3510_readB(st,0xca,&j)) < 0)
		return ret;

	deb_info("JDEC: %02x\n",j.raw);

	switch (j.JDEC_ca.JDEC) {
		case JDEC_WAIT_AT_RAM:
			deb_info("attempting to download firmware\n");
			if ((ret = bcm3510_init_cold(st)) < 0)
				return ret;
		case JDEC_EEPROM_LOAD_WAIT: /* fall-through is wanted */
			deb_info("firmware is loaded\n");
			bcm3510_check_firmware_version(st);
			break;
		default:
			return -ENODEV;
	}

	memset(&c,0,1);
	c.SEL = 1;
	bcm3510_do_hab_cmd(st,CMD_AUTO_PARAM,MSGID_SET_RF_AGC_SEL,(u8 *)&c,sizeof(c),NULL,0);

	return 0;
}