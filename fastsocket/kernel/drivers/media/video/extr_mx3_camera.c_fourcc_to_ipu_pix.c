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
typedef  enum pixel_fmt { ____Placeholder_pixel_fmt } pixel_fmt ;
typedef  int __u32 ;

/* Variables and functions */
 int IPU_PIX_FMT_GENERIC ; 
 int IPU_PIX_FMT_RGB24 ; 
 int IPU_PIX_FMT_RGB332 ; 
 int IPU_PIX_FMT_RGB565 ; 
 int IPU_PIX_FMT_YVU422P ; 
#define  V4L2_PIX_FMT_RGB24 131 
#define  V4L2_PIX_FMT_RGB332 130 
#define  V4L2_PIX_FMT_RGB565 129 
#define  V4L2_PIX_FMT_YUV422P 128 

__attribute__((used)) static enum pixel_fmt fourcc_to_ipu_pix(__u32 fourcc)
{
	/* Add more formats as need arises and test possibilities appear... */
	switch (fourcc) {
	case V4L2_PIX_FMT_RGB565:
		return IPU_PIX_FMT_RGB565;
	case V4L2_PIX_FMT_RGB24:
		return IPU_PIX_FMT_RGB24;
	case V4L2_PIX_FMT_RGB332:
		return IPU_PIX_FMT_RGB332;
	case V4L2_PIX_FMT_YUV422P:
		return IPU_PIX_FMT_YVU422P;
	default:
		return IPU_PIX_FMT_GENERIC;
	}
}