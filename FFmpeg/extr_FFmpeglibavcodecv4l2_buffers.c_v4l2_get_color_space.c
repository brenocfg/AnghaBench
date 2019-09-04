#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum v4l2_ycbcr_encoding { ____Placeholder_v4l2_ycbcr_encoding } v4l2_ycbcr_encoding ;
typedef  enum v4l2_colorspace { ____Placeholder_v4l2_colorspace } v4l2_colorspace ;
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {TYPE_5__* context; TYPE_2__ buf; } ;
typedef  TYPE_7__ V4L2Buffer ;
struct TYPE_9__ {int colorspace; int ycbcr_enc; } ;
struct TYPE_11__ {int colorspace; int ycbcr_enc; } ;
struct TYPE_12__ {TYPE_1__ pix; TYPE_3__ pix_mp; } ;
struct TYPE_14__ {TYPE_4__ fmt; } ;
struct TYPE_13__ {TYPE_6__ format; } ;

/* Variables and functions */
 int AVCOL_SPC_BT2020_CL ; 
 int AVCOL_SPC_BT2020_NCL ; 
 int AVCOL_SPC_BT470BG ; 
 int AVCOL_SPC_BT709 ; 
 int AVCOL_SPC_FCC ; 
 int AVCOL_SPC_RGB ; 
 int AVCOL_SPC_SMPTE170M ; 
 int AVCOL_SPC_SMPTE240M ; 
 int AVCOL_SPC_UNSPECIFIED ; 
#define  V4L2_COLORSPACE_470_SYSTEM_BG 134 
#define  V4L2_COLORSPACE_470_SYSTEM_M 133 
#define  V4L2_COLORSPACE_BT2020 132 
#define  V4L2_COLORSPACE_REC709 131 
#define  V4L2_COLORSPACE_SMPTE170M 130 
#define  V4L2_COLORSPACE_SMPTE240M 129 
#define  V4L2_COLORSPACE_SRGB 128 
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
 int V4L2_YCBCR_ENC_BT2020_CONST_LUM ; 

__attribute__((used)) static enum AVColorSpace v4l2_get_color_space(V4L2Buffer *buf)
{
    enum v4l2_ycbcr_encoding ycbcr;
    enum v4l2_colorspace cs;

    cs = V4L2_TYPE_IS_MULTIPLANAR(buf->buf.type) ?
        buf->context->format.fmt.pix_mp.colorspace :
        buf->context->format.fmt.pix.colorspace;

    ycbcr = V4L2_TYPE_IS_MULTIPLANAR(buf->buf.type) ?
        buf->context->format.fmt.pix_mp.ycbcr_enc:
        buf->context->format.fmt.pix.ycbcr_enc;

    switch(cs) {
    case V4L2_COLORSPACE_SRGB: return AVCOL_SPC_RGB;
    case V4L2_COLORSPACE_REC709: return AVCOL_SPC_BT709;
    case V4L2_COLORSPACE_470_SYSTEM_M: return AVCOL_SPC_FCC;
    case V4L2_COLORSPACE_470_SYSTEM_BG: return AVCOL_SPC_BT470BG;
    case V4L2_COLORSPACE_SMPTE170M: return AVCOL_SPC_SMPTE170M;
    case V4L2_COLORSPACE_SMPTE240M: return AVCOL_SPC_SMPTE240M;
    case V4L2_COLORSPACE_BT2020:
        if (ycbcr == V4L2_YCBCR_ENC_BT2020_CONST_LUM)
            return AVCOL_SPC_BT2020_CL;
        else
             return AVCOL_SPC_BT2020_NCL;
    default:
        break;
    }

    return AVCOL_SPC_UNSPECIFIED;
}