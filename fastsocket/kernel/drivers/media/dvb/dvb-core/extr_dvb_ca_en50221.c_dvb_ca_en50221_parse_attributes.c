#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct dvb_ca_private {TYPE_3__* slot_info; TYPE_2__* dvbdev; } ;
struct TYPE_6__ {int config_base; int config_option; } ;
struct TYPE_5__ {TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (char*,int,int,...) ; 
 int dvb_ca_en50221_read_tuple (struct dvb_ca_private*,int,int*,int*,int*,int*) ; 
 char* findstr (char*,int,char*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char,char,char,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int dvb_ca_en50221_parse_attributes(struct dvb_ca_private *ca, int slot)
{
	int address = 0;
	int tupleLength;
	int tupleType;
	u8 tuple[257];
	char *dvb_str;
	int rasz;
	int status;
	int got_cftableentry = 0;
	int end_chain = 0;
	int i;
	u16 manfid = 0;
	u16 devid = 0;


	// CISTPL_DEVICE_0A
	if ((status =
	     dvb_ca_en50221_read_tuple(ca, slot, &address, &tupleType, &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x1D)
		return -EINVAL;



	// CISTPL_DEVICE_0C
	if ((status =
	     dvb_ca_en50221_read_tuple(ca, slot, &address, &tupleType, &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x1C)
		return -EINVAL;



	// CISTPL_VERS_1
	if ((status =
	     dvb_ca_en50221_read_tuple(ca, slot, &address, &tupleType, &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x15)
		return -EINVAL;



	// CISTPL_MANFID
	if ((status = dvb_ca_en50221_read_tuple(ca, slot, &address, &tupleType,
						&tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x20)
		return -EINVAL;
	if (tupleLength != 4)
		return -EINVAL;
	manfid = (tuple[1] << 8) | tuple[0];
	devid = (tuple[3] << 8) | tuple[2];



	// CISTPL_CONFIG
	if ((status = dvb_ca_en50221_read_tuple(ca, slot, &address, &tupleType,
						&tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x1A)
		return -EINVAL;
	if (tupleLength < 3)
		return -EINVAL;

	/* extract the configbase */
	rasz = tuple[0] & 3;
	if (tupleLength < (3 + rasz + 14))
		return -EINVAL;
	ca->slot_info[slot].config_base = 0;
	for (i = 0; i < rasz + 1; i++) {
		ca->slot_info[slot].config_base |= (tuple[2 + i] << (8 * i));
	}

	/* check it contains the correct DVB string */
	dvb_str = findstr((char *)tuple, tupleLength, "DVB_CI_V", 8);
	if (dvb_str == NULL)
		return -EINVAL;
	if (tupleLength < ((dvb_str - (char *) tuple) + 12))
		return -EINVAL;

	/* is it a version we support? */
	if (strncmp(dvb_str + 8, "1.00", 4)) {
		printk("dvb_ca adapter %d: Unsupported DVB CAM module version %c%c%c%c\n",
		       ca->dvbdev->adapter->num, dvb_str[8], dvb_str[9], dvb_str[10], dvb_str[11]);
		return -EINVAL;
	}

	/* process the CFTABLE_ENTRY tuples, and any after those */
	while ((!end_chain) && (address < 0x1000)) {
		if ((status = dvb_ca_en50221_read_tuple(ca, slot, &address, &tupleType,
							&tupleLength, tuple)) < 0)
			return status;
		switch (tupleType) {
		case 0x1B:	// CISTPL_CFTABLE_ENTRY
			if (tupleLength < (2 + 11 + 17))
				break;

			/* if we've already parsed one, just use it */
			if (got_cftableentry)
				break;

			/* get the config option */
			ca->slot_info[slot].config_option = tuple[0] & 0x3f;

			/* OK, check it contains the correct strings */
			if ((findstr((char *)tuple, tupleLength, "DVB_HOST", 8) == NULL) ||
			    (findstr((char *)tuple, tupleLength, "DVB_CI_MODULE", 13) == NULL))
				break;

			got_cftableentry = 1;
			break;

		case 0x14:	// CISTPL_NO_LINK
			break;

		case 0xFF:	// CISTPL_END
			end_chain = 1;
			break;

		default:	/* Unknown tuple type - just skip this tuple and move to the next one */
			dprintk("dvb_ca: Skipping unknown tuple type:0x%x length:0x%x\n", tupleType,
				tupleLength);
			break;
		}
	}

	if ((address > 0x1000) || (!got_cftableentry))
		return -EINVAL;

	dprintk("Valid DVB CAM detected MANID:%x DEVID:%x CONFIGBASE:0x%x CONFIGOPTION:0x%x\n",
		manfid, devid, ca->slot_info[slot].config_base, ca->slot_info[slot].config_option);

	// success!
	return 0;
}