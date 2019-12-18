#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {scalar_t__ asf_header_read_size; scalar_t__ asf_header_size; scalar_t__ remaining_in_len; scalar_t__ asf_packet_len; } ;
struct TYPE_10__ {TYPE_3__ mms; } ;
typedef  TYPE_2__ MMSTContext ;
typedef  TYPE_3__ MMSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SC_PKT_ASF_MEDIA ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_mms_read_data (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int ff_mms_read_header (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int mms_safe_send_recv (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mms_read(URLContext *h, uint8_t *buf, int size)
{
    /* TODO: see tcp.c:tcp_read() about a possible timeout scheme */
    MMSTContext *mmst = h->priv_data;
    MMSContext *mms   = &mmst->mms;
    int result = 0;

    do {
        if(mms->asf_header_read_size < mms->asf_header_size) {
            /* Read from ASF header buffer */
            result = ff_mms_read_header(mms, buf, size);
        } else if(mms->remaining_in_len) {
            /* Read remaining packet data to buffer.
             * the result can not be zero because remaining_in_len is positive.*/
            result = ff_mms_read_data(mms, buf, size);
        } else {
            /* Read from network */
            int err = mms_safe_send_recv(mmst, NULL, SC_PKT_ASF_MEDIA);
            if (err == 0) {
                if(mms->remaining_in_len>mms->asf_packet_len) {
                    av_log(h, AV_LOG_ERROR,
                           "Incoming pktlen %d is larger than ASF pktsize %d\n",
                           mms->remaining_in_len, mms->asf_packet_len);
                    result= AVERROR(EIO);
                } else {
                    // copy the data to the packet buffer.
                    result = ff_mms_read_data(mms, buf, size);
                    if (result == 0) {
                        av_log(h, AV_LOG_TRACE, "Read ASF media packet size is zero!\n");
                        break;
                    }
                }
            } else {
                av_log(h, AV_LOG_TRACE, "read packet error!\n");
                break;
            }
        }
    } while(!result); // only return one packet.
    return result;
}