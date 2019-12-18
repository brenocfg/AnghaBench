#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_4__ {int static_payload_id; int codec_type; } ;
typedef  TYPE_1__ RTPDynamicProtocolHandler ;

/* Variables and functions */
 TYPE_1__* ff_rtp_handler_iterate (void**) ; 

const RTPDynamicProtocolHandler *ff_rtp_handler_find_by_id(int id,
                                                     enum AVMediaType codec_type)
{
    void *i = 0;
    const RTPDynamicProtocolHandler *handler;
    while (handler = ff_rtp_handler_iterate(&i)) {
        if (handler->static_payload_id && handler->static_payload_id == id &&
            codec_type == handler->codec_type)
            return handler;
    }
    return NULL;
}