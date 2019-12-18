#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int bar; scalar_t__ method; int manuf; int dev_id; int sec_prot; scalar_t__ wide; } ;
struct TYPE_4__ {TYPE_1__ flash; } ;
struct asd_ha_struct {TYPE_2__ hw_prof; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int,...) ; 
 int FAIL_FIND_FLASH_ID ; 
#define  FLASH_DEV_ID_AM29F800B 144 
#define  FLASH_DEV_ID_AM29LV008BT 143 
#define  FLASH_DEV_ID_AM29LV640MT 142 
#define  FLASH_DEV_ID_AM29LV800DT 141 
#define  FLASH_DEV_ID_I28LV00TAT 140 
#define  FLASH_DEV_ID_MBM29DL800TA 139 
#define  FLASH_DEV_ID_MBM29LV008TA 138 
#define  FLASH_DEV_ID_MBM29LV800TE 137 
#define  FLASH_DEV_ID_MX29LV800BT 136 
#define  FLASH_DEV_ID_STM29008 135 
#define  FLASH_DEV_ID_STM29LV640 134 
#define  FLASH_DEV_ID_STM29W800DT 133 
 int FLASH_DEV_ID_UNKNOWN ; 
#define  FLASH_MANUF_ID_AMD 132 
#define  FLASH_MANUF_ID_FUJITSU 131 
#define  FLASH_MANUF_ID_INTEL 130 
#define  FLASH_MANUF_ID_MACRONIX 129 
#define  FLASH_MANUF_ID_ST 128 
 int FLASH_MANUF_ID_UNKNOWN ; 
 void* FLASH_METHOD_A ; 
 void* FLASH_METHOD_B ; 
 scalar_t__ FLASH_METHOD_UNKNOWN ; 
 int asd_read_reg_byte (struct asd_ha_struct*,int) ; 
 int asd_reset_flash (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,int,int) ; 

int asd_check_flash_type(struct asd_ha_struct *asd_ha)
{
	u8 manuf_id;
	u8 dev_id;
	u8 sec_prot;
	u32 inc;
	u32 reg;
	int err;

	/* get Flash memory base address */
	reg = asd_ha->hw_prof.flash.bar;

	/* Determine flash info */
	err = asd_reset_flash(asd_ha);
	if (err) {
		ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
		return err;
	}

	asd_ha->hw_prof.flash.method = FLASH_METHOD_UNKNOWN;
	asd_ha->hw_prof.flash.manuf = FLASH_MANUF_ID_UNKNOWN;
	asd_ha->hw_prof.flash.dev_id = FLASH_DEV_ID_UNKNOWN;

	/* Get flash info. This would most likely be AMD Am29LV family flash.
	 * First try the sequence for word mode.  It is the same as for
	 * 008B (byte mode only), 160B (word mode) and 800D (word mode).
	 */
	inc = asd_ha->hw_prof.flash.wide ? 2 : 1;
	asd_write_reg_byte(asd_ha, reg + 0xAAA, 0xAA);
	asd_write_reg_byte(asd_ha, reg + 0x555, 0x55);
	asd_write_reg_byte(asd_ha, reg + 0xAAA, 0x90);
	manuf_id = asd_read_reg_byte(asd_ha, reg);
	dev_id = asd_read_reg_byte(asd_ha, reg + inc);
	sec_prot = asd_read_reg_byte(asd_ha, reg + inc + inc);
	/* Get out of autoselect mode. */
	err = asd_reset_flash(asd_ha);
	if (err) {
		ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
		return err;
	}
	ASD_DPRINTK("Flash MethodA manuf_id(0x%x) dev_id(0x%x) "
		"sec_prot(0x%x)\n", manuf_id, dev_id, sec_prot);
	err = asd_reset_flash(asd_ha);
	if (err != 0)
		return err;

	switch (manuf_id) {
	case FLASH_MANUF_ID_AMD:
		switch (sec_prot) {
		case FLASH_DEV_ID_AM29LV800DT:
		case FLASH_DEV_ID_AM29LV640MT:
		case FLASH_DEV_ID_AM29F800B:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			break;
		default:
			break;
		}
		break;
	case FLASH_MANUF_ID_ST:
		switch (sec_prot) {
		case FLASH_DEV_ID_STM29W800DT:
		case FLASH_DEV_ID_STM29LV640:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			break;
		default:
			break;
		}
		break;
	case FLASH_MANUF_ID_FUJITSU:
		switch (sec_prot) {
		case FLASH_DEV_ID_MBM29LV800TE:
		case FLASH_DEV_ID_MBM29DL800TA:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			break;
		}
		break;
	case FLASH_MANUF_ID_MACRONIX:
		switch (sec_prot) {
		case FLASH_DEV_ID_MX29LV800BT:
			asd_ha->hw_prof.flash.method = FLASH_METHOD_A;
			break;
		}
		break;
	}

	if (asd_ha->hw_prof.flash.method == FLASH_METHOD_UNKNOWN) {
		err = asd_reset_flash(asd_ha);
		if (err) {
			ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
			return err;
		}

		/* Issue Unlock sequence for AM29LV008BT */
		asd_write_reg_byte(asd_ha, (reg + 0x555), 0xAA);
		asd_write_reg_byte(asd_ha, (reg + 0x2AA), 0x55);
		asd_write_reg_byte(asd_ha, (reg + 0x555), 0x90);
		manuf_id = asd_read_reg_byte(asd_ha, reg);
		dev_id = asd_read_reg_byte(asd_ha, reg + inc);
		sec_prot = asd_read_reg_byte(asd_ha, reg + inc + inc);

		ASD_DPRINTK("Flash MethodB manuf_id(0x%x) dev_id(0x%x) sec_prot"
			"(0x%x)\n", manuf_id, dev_id, sec_prot);

		err = asd_reset_flash(asd_ha);
		if (err != 0) {
			ASD_DPRINTK("couldn't reset flash. err=%d\n", err);
			return err;
		}

		switch (manuf_id) {
		case FLASH_MANUF_ID_AMD:
			switch (dev_id) {
			case FLASH_DEV_ID_AM29LV008BT:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				break;
			default:
				break;
			}
			break;
		case FLASH_MANUF_ID_ST:
			switch (dev_id) {
			case FLASH_DEV_ID_STM29008:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				break;
			default:
				break;
			}
			break;
		case FLASH_MANUF_ID_FUJITSU:
			switch (dev_id) {
			case FLASH_DEV_ID_MBM29LV008TA:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				break;
			}
			break;
		case FLASH_MANUF_ID_INTEL:
			switch (dev_id) {
			case FLASH_DEV_ID_I28LV00TAT:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				break;
			}
			break;
		case FLASH_MANUF_ID_MACRONIX:
			switch (dev_id) {
			case FLASH_DEV_ID_I28LV00TAT:
				asd_ha->hw_prof.flash.method = FLASH_METHOD_B;
				break;
			}
			break;
		default:
			return FAIL_FIND_FLASH_ID;
		}
	}

	if (asd_ha->hw_prof.flash.method == FLASH_METHOD_UNKNOWN)
	      return FAIL_FIND_FLASH_ID;

	asd_ha->hw_prof.flash.manuf = manuf_id;
	asd_ha->hw_prof.flash.dev_id = dev_id;
	asd_ha->hw_prof.flash.sec_prot = sec_prot;
	return 0;
}