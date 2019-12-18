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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVColorRange { ____Placeholder_AVColorRange } AVColorRange ;
typedef  int /*<<< orphan*/  RaPixelRange ;

/* Variables and functions */
#define  AVCOL_RANGE_JPEG 132 
#define  AVCOL_RANGE_MPEG 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  RA_PIXEL_RANGE_FULL ; 
 int /*<<< orphan*/  RA_PIXEL_RANGE_LIMITED ; 

__attribute__((used)) static inline RaPixelRange range_map(enum AVPixelFormat pix_fmt, enum AVColorRange range)
{
    switch (pix_fmt) {
    case AV_PIX_FMT_YUVJ420P:
    case AV_PIX_FMT_YUVJ422P:
    case AV_PIX_FMT_YUVJ444P:
        return RA_PIXEL_RANGE_FULL;
    }

    switch (range) {
    case AVCOL_RANGE_JPEG:
        return RA_PIXEL_RANGE_FULL;
    case AVCOL_RANGE_MPEG:
    default:
        return RA_PIXEL_RANGE_LIMITED;
    }
}