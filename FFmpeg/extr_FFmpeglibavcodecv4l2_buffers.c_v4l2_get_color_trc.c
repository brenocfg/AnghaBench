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
typedef  enum v4l2_xfer_func { ____Placeholder_v4l2_xfer_func } v4l2_xfer_func ;
typedef  enum v4l2_colorspace { ____Placeholder_v4l2_colorspace } v4l2_colorspace ;
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {TYPE_6__* context; TYPE_1__ buf; } ;
typedef  TYPE_7__ V4L2Buffer ;
struct TYPE_11__ {int colorspace; int ycbcr_enc; int xfer_func; } ;
struct TYPE_10__ {int colorspace; int ycbcr_enc; int xfer_func; } ;
struct TYPE_12__ {TYPE_3__ pix; TYPE_2__ pix_mp; } ;
struct TYPE_13__ {TYPE_4__ fmt; } ;
struct TYPE_14__ {TYPE_5__ format; } ;

/* Variables and functions */
 int AVCOL_TRC_BT1361_ECG ; 
 int AVCOL_TRC_BT709 ; 
 int AVCOL_TRC_GAMMA22 ; 
 int AVCOL_TRC_GAMMA28 ; 
 int AVCOL_TRC_IEC61966_2_1 ; 
 int AVCOL_TRC_SMPTE170M ; 
 int AVCOL_TRC_SMPTE240M ; 
 int AVCOL_TRC_UNSPECIFIED ; 
#define  V4L2_COLORSPACE_470_SYSTEM_BG 135 
#define  V4L2_COLORSPACE_470_SYSTEM_M 134 
#define  V4L2_COLORSPACE_SMPTE170M 133 
#define  V4L2_COLORSPACE_SMPTE240M 132 
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
#define  V4L2_XFER_FUNC_709 131 
#define  V4L2_XFER_FUNC_SRGB 130 
#define  V4L2_YCBCR_ENC_XV601 129 
#define  V4L2_YCBCR_ENC_XV709 128 

__attribute__((used)) static enum AVColorTransferCharacteristic v4l2_get_color_trc(V4L2Buffer *buf)
{
    enum v4l2_ycbcr_encoding ycbcr;
    enum v4l2_xfer_func xfer;
    enum v4l2_colorspace cs;

    cs = V4L2_TYPE_IS_MULTIPLANAR(buf->buf.type) ?
        buf->context->format.fmt.pix_mp.colorspace :
        buf->context->format.fmt.pix.colorspace;

    ycbcr = V4L2_TYPE_IS_MULTIPLANAR(buf->buf.type) ?
        buf->context->format.fmt.pix_mp.ycbcr_enc:
        buf->context->format.fmt.pix.ycbcr_enc;

    xfer = V4L2_TYPE_IS_MULTIPLANAR(buf->buf.type) ?
        buf->context->format.fmt.pix_mp.xfer_func:
        buf->context->format.fmt.pix.xfer_func;

    switch (xfer) {
    case V4L2_XFER_FUNC_709: return AVCOL_TRC_BT709;
    case V4L2_XFER_FUNC_SRGB: return AVCOL_TRC_IEC61966_2_1;
    default:
        break;
    }

    switch (cs) {
    case V4L2_COLORSPACE_470_SYSTEM_M: return AVCOL_TRC_GAMMA22;
    case V4L2_COLORSPACE_470_SYSTEM_BG: return AVCOL_TRC_GAMMA28;
    case V4L2_COLORSPACE_SMPTE170M: return AVCOL_TRC_SMPTE170M;
    case V4L2_COLORSPACE_SMPTE240M: return AVCOL_TRC_SMPTE240M;
    default:
        break;
    }

    switch (ycbcr) {
    case V4L2_YCBCR_ENC_XV709:
    case V4L2_YCBCR_ENC_XV601: return AVCOL_TRC_BT1361_ECG;
    default:
        break;
    }

    return AVCOL_TRC_UNSPECIFIED;
}