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
struct TYPE_2__ {struct em28xx* priv; } ;
struct em28xx_dvb {TYPE_1__ adapter; } ;
struct em28xx {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_DIGITAL_MODE ; 
 int /*<<< orphan*/  EM28XX_DVB_MAX_PACKETS ; 
 int /*<<< orphan*/  EM28XX_DVB_NUM_BUFS ; 
 int /*<<< orphan*/  dvb_isoc_copy ; 
 int em28xx_init_isoc (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int em28xx_isoc_dvb_max_packetsize (struct em28xx*) ; 
 int em28xx_set_mode (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int start_streaming(struct em28xx_dvb *dvb)
{
	int rc;
	struct em28xx *dev = dvb->adapter.priv;
	int max_dvb_packet_size;

	usb_set_interface(dev->udev, 0, 1);
	rc = em28xx_set_mode(dev, EM28XX_DIGITAL_MODE);
	if (rc < 0)
		return rc;

	max_dvb_packet_size = em28xx_isoc_dvb_max_packetsize(dev);

	return em28xx_init_isoc(dev, EM28XX_DVB_MAX_PACKETS,
				EM28XX_DVB_NUM_BUFS, max_dvb_packet_size,
				dvb_isoc_copy);
}