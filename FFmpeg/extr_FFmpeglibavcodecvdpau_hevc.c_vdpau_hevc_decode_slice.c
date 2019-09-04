#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct vdpau_picture_context {int dummy; } ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {TYPE_1__* ref; } ;
struct TYPE_5__ {struct vdpau_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_2__ HEVCContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int ff_vdpau_add_buffer (struct vdpau_picture_context*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* start_code_prefix ; 

__attribute__((used)) static int vdpau_hevc_decode_slice(AVCodecContext *avctx,
                                   const uint8_t *buffer, uint32_t size)
{
    HEVCContext *h = avctx->priv_data;
    struct vdpau_picture_context *pic_ctx = h->ref->hwaccel_picture_private;
    int val;

    val = ff_vdpau_add_buffer(pic_ctx, start_code_prefix, 3);
    if (val)
        return val;

    val = ff_vdpau_add_buffer(pic_ctx, buffer, size);
    if (val)
        return val;

    return 0;
}