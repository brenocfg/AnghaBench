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
struct em28xx {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_EM2874 ; 
#define  EM28XX_CHIPCFG2_TS_PACKETSIZE_188 131 
#define  EM28XX_CHIPCFG2_TS_PACKETSIZE_376 130 
#define  EM28XX_CHIPCFG2_TS_PACKETSIZE_564 129 
#define  EM28XX_CHIPCFG2_TS_PACKETSIZE_752 128 
 unsigned int EM28XX_CHIPCFG2_TS_PACKETSIZE_MASK ; 
 int /*<<< orphan*/  EM28XX_R01_CHIPCFG2 ; 
 int /*<<< orphan*/  em28xx_coredbg (char*,unsigned int) ; 
 unsigned int em28xx_read_reg (struct em28xx*,int /*<<< orphan*/ ) ; 

int em28xx_isoc_dvb_max_packetsize(struct em28xx *dev)
{
	unsigned int chip_cfg2;
	unsigned int packet_size = 564;

	if (dev->chip_id == CHIP_ID_EM2874) {
		/* FIXME - for now assume 564 like it was before, but the
		   em2874 code should be added to return the proper value... */
		packet_size = 564;
	} else {
		/* TS max packet size stored in bits 1-0 of R01 */
		chip_cfg2 = em28xx_read_reg(dev, EM28XX_R01_CHIPCFG2);
		switch (chip_cfg2 & EM28XX_CHIPCFG2_TS_PACKETSIZE_MASK) {
		case EM28XX_CHIPCFG2_TS_PACKETSIZE_188:
			packet_size = 188;
			break;
		case EM28XX_CHIPCFG2_TS_PACKETSIZE_376:
			packet_size = 376;
			break;
		case EM28XX_CHIPCFG2_TS_PACKETSIZE_564:
			packet_size = 564;
			break;
		case EM28XX_CHIPCFG2_TS_PACKETSIZE_752:
			packet_size = 752;
			break;
		}
	}

	em28xx_coredbg("dvb max packet size=%d\n", packet_size);
	return packet_size;
}