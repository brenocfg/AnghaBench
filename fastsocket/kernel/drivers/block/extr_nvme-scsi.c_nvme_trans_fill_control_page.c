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
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int MODE_PAGE_CONTROL ; 
 int MODE_PAGE_CONTROL_LEN ; 
 int MODE_PAGE_CONTROL_LEN_FIELD ; 
 int SNTI_INTERNAL_ERROR ; 
 int SNTI_TRANSLATION_SUCCESS ; 

__attribute__((used)) static int nvme_trans_fill_control_page(struct nvme_ns *ns,
					struct sg_io_hdr *hdr, u8 *resp,
					int len)
{
	if (len < MODE_PAGE_CONTROL_LEN)
		return SNTI_INTERNAL_ERROR;

	resp[0] = MODE_PAGE_CONTROL;
	resp[1] = MODE_PAGE_CONTROL_LEN_FIELD;
	resp[2] = 0x0E;		/* TST=000b, TMF_ONLY=0, DPICZ=1,
				 * D_SENSE=1, GLTSD=1, RLEC=0 */
	resp[3] = 0x12;		/* Q_ALGO_MODIFIER=1h, NUAR=0, QERR=01b */
	/* Byte 4:  VS=0, RAC=0, UA_INT=0, SWP=0 */
	resp[5] = 0x40;		/* ATO=0, TAS=1, ATMPE=0, RWWP=0, AUTOLOAD=0 */
	/* resp[6] and [7] are obsolete, thus zero */
	resp[8] = 0xFF;		/* Busy timeout period = 0xffff */
	resp[9] = 0xFF;
	/* Bytes 10,11: Extended selftest completion time = 0x0000 */

	return SNTI_TRANSLATION_SUCCESS;
}