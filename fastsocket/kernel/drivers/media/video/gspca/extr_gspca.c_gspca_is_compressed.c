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
typedef  int __u32 ;

/* Variables and functions */
#define  V4L2_PIX_FMT_JPEG 132 
#define  V4L2_PIX_FMT_MJPEG 131 
#define  V4L2_PIX_FMT_MR97310A 130 
#define  V4L2_PIX_FMT_PAC207 129 
#define  V4L2_PIX_FMT_SPCA561 128 

__attribute__((used)) static int gspca_is_compressed(__u32 format)
{
	switch (format) {
	case V4L2_PIX_FMT_MJPEG:
	case V4L2_PIX_FMT_JPEG:
	case V4L2_PIX_FMT_SPCA561:
	case V4L2_PIX_FMT_PAC207:
	case V4L2_PIX_FMT_MR97310A:
		return 1;
	}
	return 0;
}