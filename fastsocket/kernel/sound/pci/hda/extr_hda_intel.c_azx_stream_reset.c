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
struct azx_dev {scalar_t__* posbuf; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CTL ; 
 unsigned char SD_CTL_STREAM_RESET ; 
 unsigned char azx_sd_readb (struct azx_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_sd_writeb (struct azx_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  azx_stream_clear (struct azx*,struct azx_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void azx_stream_reset(struct azx *chip, struct azx_dev *azx_dev)
{
	unsigned char val;
	int timeout;

	azx_stream_clear(chip, azx_dev);

	azx_sd_writeb(azx_dev, SD_CTL, azx_sd_readb(azx_dev, SD_CTL) |
		      SD_CTL_STREAM_RESET);
	udelay(3);
	timeout = 300;
	while (!((val = azx_sd_readb(azx_dev, SD_CTL)) & SD_CTL_STREAM_RESET) &&
	       --timeout)
		;
	val &= ~SD_CTL_STREAM_RESET;
	azx_sd_writeb(azx_dev, SD_CTL, val);
	udelay(3);

	timeout = 300;
	/* waiting for hardware to report that the stream is out of reset */
	while (((val = azx_sd_readb(azx_dev, SD_CTL)) & SD_CTL_STREAM_RESET) &&
	       --timeout)
		;

	/* reset first position - may not be synced with hw at this time */
	*azx_dev->posbuf = 0;
}