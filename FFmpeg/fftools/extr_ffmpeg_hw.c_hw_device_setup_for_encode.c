#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  device_ref; } ;
struct TYPE_7__ {TYPE_1__* enc_ctx; int /*<<< orphan*/  enc; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_device_ctx; } ;
typedef  TYPE_2__ OutputStream ;
typedef  TYPE_3__ HWDevice ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 TYPE_3__* hw_device_match_by_codec (int /*<<< orphan*/ ) ; 

int hw_device_setup_for_encode(OutputStream *ost)
{
    HWDevice *dev;

    dev = hw_device_match_by_codec(ost->enc);
    if (dev) {
        ost->enc_ctx->hw_device_ctx = av_buffer_ref(dev->device_ref);
        if (!ost->enc_ctx->hw_device_ctx)
            return AVERROR(ENOMEM);
        return 0;
    } else {
        // No device required, or no device available.
        return 0;
    }
}