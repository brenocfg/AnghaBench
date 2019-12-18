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
struct TYPE_3__ {unsigned long urb_count; unsigned long iso_skip_count; unsigned long iso_err_count; unsigned long data_count; } ;
struct uvd {unsigned long iso_packet_len; TYPE_2__* dev; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long CAMERA_URB_FRAMES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long,char,unsigned long) ; 

__attribute__((used)) static void usbvideo_ReportStatistics(const struct uvd *uvd)
{
	if ((uvd != NULL) && (uvd->stats.urb_count > 0)) {
		unsigned long allPackets, badPackets, goodPackets, percent;
		allPackets = uvd->stats.urb_count * CAMERA_URB_FRAMES;
		badPackets = uvd->stats.iso_skip_count + uvd->stats.iso_err_count;
		goodPackets = allPackets - badPackets;
		/* Calculate percentage wisely, remember integer limits */
		assert(allPackets != 0);
		if (goodPackets < (((unsigned long)-1)/100))
			percent = (100 * goodPackets) / allPackets;
		else
			percent = goodPackets / (allPackets / 100);
		dev_info(&uvd->dev->dev,
			 "Packet Statistics: Total=%lu. Empty=%lu. Usage=%lu%%\n",
			 allPackets, badPackets, percent);
		if (uvd->iso_packet_len > 0) {
			unsigned long allBytes, xferBytes;
			char multiplier = ' ';
			allBytes = allPackets * uvd->iso_packet_len;
			xferBytes = uvd->stats.data_count;
			assert(allBytes != 0);
			if (xferBytes < (((unsigned long)-1)/100))
				percent = (100 * xferBytes) / allBytes;
			else
				percent = xferBytes / (allBytes / 100);
			/* Scale xferBytes for easy reading */
			if (xferBytes > 10*1024) {
				xferBytes /= 1024;
				multiplier = 'K';
				if (xferBytes > 10*1024) {
					xferBytes /= 1024;
					multiplier = 'M';
					if (xferBytes > 10*1024) {
						xferBytes /= 1024;
						multiplier = 'G';
						if (xferBytes > 10*1024) {
							xferBytes /= 1024;
							multiplier = 'T';
						}
					}
				}
			}
			dev_info(&uvd->dev->dev,
				 "Transfer Statistics: Transferred=%lu%cB Usage=%lu%%\n",
				 xferBytes, multiplier, percent);
		}
	}
}