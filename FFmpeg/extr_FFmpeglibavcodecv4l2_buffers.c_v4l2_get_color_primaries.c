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
typedef  enum AVColorPrimaries { ____Placeholder_AVColorPrimaries } AVColorPrimaries ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {TYPE_6__* context; TYPE_2__ buf; } ;
typedef  TYPE_7__ V4L2Buffer ;
struct TYPE_9__ {int colorspace; int ycbcr_enc; } ;
struct TYPE_11__ {int colorspace; int ycbcr_enc; } ;
struct TYPE_12__ {TYPE_1__ pix; TYPE_3__ pix_mp; } ;
struct TYPE_13__ {TYPE_4__ fmt; } ;
struct TYPE_14__ {TYPE_5__ format; } ;

/* Variables and functions */
 int AVCOL_PRI_BT2020 ; 
 int AVCOL_PRI_BT470BG ; 
 int AVCOL_PRI_BT470M ; 
 int AVCOL_PRI_BT709 ; 
 int AVCOL_PRI_SMPTE170M ; 
 int AVCOL_PRI_SMPTE240M ; 
 int AVCOL_PRI_UNSPECIFIED ; 
#define  V4L2_COLORSPACE_470_SYSTEM_BG 135 
#define  V4L2_COLORSPACE_BT2020 134 
#define  V4L2_COLORSPACE_SMPTE170M 133 
#define  V4L2_COLORSPACE_SMPTE240M 132 
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
#define  V4L2_YCBCR_ENC_601 131 
#define  V4L2_YCBCR_ENC_709 130 
#define  V4L2_YCBCR_ENC_XV601 129 
#define  V4L2_YCBCR_ENC_XV709 128 

__attribute__((used)) static enum AVColorPrimaries v4l2_get_color_primaries(V4L2Buffer *buf)
{
    enum v4l2_ycbcr_encoding ycbcr;
    enum v4l2_colorspace cs;

    cs = V4L2_TYPE_IS_MULTIPLANAR(buf->buf.type) ?
        buf->context->format.fmt.pix_mp.colorspace :
        buf->context->format.fmt.pix.colorspace;

    ycbcr = V4L2_TYPE_IS_MULTIPLANAR(buf->buf.type) ?
        buf->context->format.fmt.pix_mp.ycbcr_enc:
        buf->context->format.fmt.pix.ycbcr_enc;

    switch(ycbcr) {
    case V4L2_YCBCR_ENC_XV709:
    case V4L2_YCBCR_ENC_709: return AVCOL_PRI_BT709;
    case V4L2_YCBCR_ENC_XV601:
    case V4L2_YCBCR_ENC_601:return AVCOL_PRI_BT470M;
    default:
        break;
    }

    switch(cs) {
    case V4L2_COLORSPACE_470_SYSTEM_BG: return AVCOL_PRI_BT470BG;
    case V4L2_COLORSPACE_SMPTE170M: return AVCOL_PRI_SMPTE170M;
    case V4L2_COLORSPACE_SMPTE240M: return AVCOL_PRI_SMPTE240M;
    case V4L2_COLORSPACE_BT2020: return AVCOL_PRI_BT2020;
    default:
        break;
    }

    return AVCOL_PRI_UNSPECIFIED;
}