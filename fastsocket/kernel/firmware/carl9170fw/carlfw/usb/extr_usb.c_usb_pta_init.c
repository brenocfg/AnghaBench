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
struct TYPE_3__ {int /*<<< orphan*/ * os_cfg_desc; int /*<<< orphan*/ * cfg_desc; } ;
struct TYPE_4__ {TYPE_1__ usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_PTA_DMA_MODE_CTRL_DISABLE_USB ; 
 int /*<<< orphan*/  AR9170_PTA_DMA_MODE_CTRL_RESET ; 
 int /*<<< orphan*/  AR9170_PTA_REG_DMA_MODE_CTRL ; 
 unsigned int AR9170_USB_DMA_CTL_DOWN_STREAM ; 
 unsigned int AR9170_USB_DMA_CTL_ENABLE_FROM_DEVICE ; 
 unsigned int AR9170_USB_DMA_CTL_ENABLE_TO_DEVICE ; 
 unsigned int AR9170_USB_DMA_CTL_HIGH_SPEED ; 
 unsigned int AR9170_USB_DMA_CTL_UP_PACKET_MODE ; 
 unsigned int AR9170_USB_DMA_CTL_UP_STREAM_16K ; 
 unsigned int AR9170_USB_DMA_CTL_UP_STREAM_32K ; 
 unsigned int AR9170_USB_DMA_CTL_UP_STREAM_4K ; 
 unsigned int AR9170_USB_DMA_CTL_UP_STREAM_8K ; 
 int /*<<< orphan*/  AR9170_USB_REG_DMA_CTL ; 
 int /*<<< orphan*/  AR9170_USB_REG_MAX_AGG_UPLOAD ; 
 int /*<<< orphan*/  AR9170_USB_REG_UPLOAD_TIME_CTL ; 
 int /*<<< orphan*/  andl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fw ; 
 int /*<<< orphan*/  orl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usb_config_fullspeed ; 
 int /*<<< orphan*/  usb_config_highspeed ; 
 scalar_t__ usb_detect_highspeed () ; 

__attribute__((used)) static void usb_pta_init(void)
{
	unsigned int usb_dma_ctrl = 0;
	/* Set PTA mode to USB */
	andl(AR9170_PTA_REG_DMA_MODE_CTRL,
		~AR9170_PTA_DMA_MODE_CTRL_DISABLE_USB);

	/* Do a software reset to PTA component */
	orl(AR9170_PTA_REG_DMA_MODE_CTRL, AR9170_PTA_DMA_MODE_CTRL_RESET);
	andl(AR9170_PTA_REG_DMA_MODE_CTRL, ~AR9170_PTA_DMA_MODE_CTRL_RESET);

	if (usb_detect_highspeed()) {
		fw.usb.os_cfg_desc = &usb_config_fullspeed;
		fw.usb.cfg_desc = &usb_config_highspeed;

		/* 512 Byte DMA transfers */
		usb_dma_ctrl |= AR9170_USB_DMA_CTL_HIGH_SPEED;
	} else {
		fw.usb.cfg_desc = &usb_config_fullspeed;
		fw.usb.os_cfg_desc = &usb_config_highspeed;
	}

#ifdef CONFIG_CARL9170FW_USB_UP_STREAM
# if (CONFIG_CARL9170FW_RX_FRAME_LEN == 4096)
	usb_dma_ctrl |= AR9170_USB_DMA_CTL_UP_STREAM_4K;
# elif (CONFIG_CARL9170FW_RX_FRAME_LEN == 8192)
	usb_dma_ctrl |= AR9170_USB_DMA_CTL_UP_STREAM_8K;
# elif (CONFIG_CARL9170FW_RX_FRAME_LEN == 16384)
	usb_dma_ctrl |= AR9170_USB_DMA_CTL_UP_STREAM_16K;
# elif (CONFIG_CARL9170FW_RX_FRAME_LEN == 32768)
	usb_dma_ctrl |= AR9170_USB_DMA_CTL_UP_STREAM_32K;
# else
#	error "Invalid AR9170_RX_FRAME_LEN setting"
# endif

#else /* CONFIG_CARL9170FW_USB_UP_STREAM */
	usb_dma_ctrl |= AR9170_USB_DMA_CTL_UP_PACKET_MODE;
#endif /* CONFIG_CARL9170FW_USB_UP_STREAM */

#ifdef CONFIG_CARL9170FW_USB_DOWN_STREAM
	/* Enable down stream mode */
	usb_dma_ctrl |= AR9170_USB_DMA_CTL_DOWN_STREAM;
#endif /* CONFIG_CARL9170FW_USB_DOWN_STREAM */

#ifdef CONFIG_CARL9170FW_USB_UP_STREAM
	/* Set the up stream mode maximum aggregate number */
	set(AR9170_USB_REG_MAX_AGG_UPLOAD, 4);

	/*
	 * Set the up stream mode timeout value.
	 * NB: The vendor driver (otus) set 0x80?
	 */
	set(AR9170_USB_REG_UPLOAD_TIME_CTL, 0x80);
#endif /* CONFIG_CARL9170FW_USB_UP_STREAM */

	/* Enable up stream and down stream */
	usb_dma_ctrl |= AR9170_USB_DMA_CTL_ENABLE_TO_DEVICE |
	    AR9170_USB_DMA_CTL_ENABLE_FROM_DEVICE;

	set(AR9170_USB_REG_DMA_CTL, usb_dma_ctrl);
}