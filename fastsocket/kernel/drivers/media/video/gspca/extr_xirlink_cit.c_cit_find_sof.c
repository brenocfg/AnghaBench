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
struct sd {int model; int sof_read; int /*<<< orphan*/  sof_len; } ;
struct gspca_dev {int /*<<< orphan*/  width; } ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int,int,int,...) ; 

__attribute__((used)) static u8 *cit_find_sof(struct gspca_dev *gspca_dev, u8 *data, int len)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 byte3 = 0, byte4 = 0;
	int i;

	switch (sd->model) {
	case CIT_MODEL0:
	case CIT_MODEL1:
	case CIT_MODEL3:
	case CIT_IBM_NETCAM_PRO:
		switch (gspca_dev->width) {
		case 160: /* 160x120 */
			byte3 = 0x02;
			byte4 = 0x0a;
			break;
		case 176: /* 176x144 */
			byte3 = 0x02;
			byte4 = 0x0e;
			break;
		case 320: /* 320x240 */
			byte3 = 0x02;
			byte4 = 0x08;
			break;
		case 352: /* 352x288 */
			byte3 = 0x02;
			byte4 = 0x00;
			break;
		case 640:
			byte3 = 0x03;
			byte4 = 0x08;
			break;
		}

		/* These have a different byte3 */
		if (sd->model <= CIT_MODEL1)
			byte3 = 0x00;

		for (i = 0; i < len; i++) {
			/* For this model the SOF always starts at offset 0
			   so no need to search the entire frame */
			if (sd->model == CIT_MODEL0 && sd->sof_read != i)
				break;

			switch (sd->sof_read) {
			case 0:
				if (data[i] == 0x00)
					sd->sof_read++;
				break;
			case 1:
				if (data[i] == 0xff)
					sd->sof_read++;
				else if (data[i] == 0x00)
					sd->sof_read = 1;
				else
					sd->sof_read = 0;
				break;
			case 2:
				if (data[i] == byte3)
					sd->sof_read++;
				else if (data[i] == 0x00)
					sd->sof_read = 1;
				else
					sd->sof_read = 0;
				break;
			case 3:
				if (data[i] == byte4) {
					sd->sof_read = 0;
					return data + i + (sd->sof_len - 3);
				}
				if (byte3 == 0x00 && data[i] == 0xff)
					sd->sof_read = 2;
				else if (data[i] == 0x00)
					sd->sof_read = 1;
				else
					sd->sof_read = 0;
				break;
			}
		}
		break;
	case CIT_MODEL2:
	case CIT_MODEL4:
		/* TESTME we need to find a longer sof signature to avoid
		   false positives */
		for (i = 0; i < len; i++) {
			switch (sd->sof_read) {
			case 0:
				if (data[i] == 0x00)
					sd->sof_read++;
				break;
			case 1:
				sd->sof_read = 0;
				if (data[i] == 0xff) {
					if (i >= 4)
						PDEBUG(D_FRAM,
						       "header found at offset: %d: %02x %02x 00 %02x %02x %02x\n",
						       i - 1,
						       data[i - 4],
						       data[i - 3],
						       data[i],
						       data[i + 1],
						       data[i + 2]);
					else
						PDEBUG(D_FRAM,
						       "header found at offset: %d: 00 %02x %02x %02x\n",
						       i - 1,
						       data[i],
						       data[i + 1],
						       data[i + 2]);
					return data + i + (sd->sof_len - 1);
				}
				break;
			}
		}
		break;
	}
	return NULL;
}