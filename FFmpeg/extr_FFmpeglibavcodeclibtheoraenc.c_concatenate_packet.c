#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_1__ ogg_packet ;
struct TYPE_7__ {int extradata_size; scalar_t__ extradata; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WB16 (scalar_t__,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int av_reallocp (scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int concatenate_packet(unsigned int* offset,
                              AVCodecContext* avc_context,
                              const ogg_packet* packet)
{
    const char* message = NULL;
    int newsize = avc_context->extradata_size + 2 + packet->bytes;
    int err = AVERROR_INVALIDDATA;

    if (packet->bytes < 0) {
        message = "ogg_packet has negative size";
    } else if (packet->bytes > 0xffff) {
        message = "ogg_packet is larger than 65535 bytes";
    } else if (newsize < avc_context->extradata_size) {
        message = "extradata_size would overflow";
    } else {
        if ((err = av_reallocp(&avc_context->extradata, newsize)) < 0) {
            avc_context->extradata_size = 0;
            message = "av_realloc failed";
        }
    }
    if (message) {
        av_log(avc_context, AV_LOG_ERROR, "concatenate_packet failed: %s\n", message);
        return err;
    }

    avc_context->extradata_size = newsize;
    AV_WB16(avc_context->extradata + (*offset), packet->bytes);
    *offset += 2;
    memcpy(avc_context->extradata + (*offset), packet->packet, packet->bytes);
    (*offset) += packet->bytes;
    return 0;
}