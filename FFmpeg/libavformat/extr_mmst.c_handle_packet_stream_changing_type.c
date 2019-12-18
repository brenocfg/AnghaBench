#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mms_hd; scalar_t__ in_buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  header_packet_id; TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSTContext ;
typedef  TYPE_2__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  AV_RL32 (scalar_t__) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void handle_packet_stream_changing_type(MMSTContext *mmst)
{
    MMSContext *mms = &mmst->mms;
    av_log(mms->mms_hd, AV_LOG_TRACE, "Stream changing!\n");

    // 40 is the packet header size, 7 is the prefix size.
    mmst->header_packet_id= AV_RL32(mms->in_buffer + 40 + 7);
    av_log(mms->mms_hd, AV_LOG_TRACE, "Changed header prefix to 0x%x", mmst->header_packet_id);
}