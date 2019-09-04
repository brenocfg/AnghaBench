#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int stream_num; int /*<<< orphan*/  write_out_ptr; TYPE_1__* streams; } ;
struct TYPE_8__ {TYPE_3__ mms; } ;
struct TYPE_7__ {int id; } ;
typedef  TYPE_2__ MMSTContext ;
typedef  TYPE_3__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PKT_STREAM_ID_REQUEST ; 
 int /*<<< orphan*/  bytestream_put_le16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ *,int) ; 
 int send_command_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  start_command_packet (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_stream_selection_request(MMSTContext *mmst)
{
    int i;
    MMSContext *mms = &mmst->mms;
    //  send the streams we want back...
    start_command_packet(mmst, CS_PKT_STREAM_ID_REQUEST);
    bytestream_put_le32(&mms->write_out_ptr, mms->stream_num);         // stream nums
    for(i= 0; i<mms->stream_num; i++) {
        bytestream_put_le16(&mms->write_out_ptr, 0xffff);              // flags
        bytestream_put_le16(&mms->write_out_ptr, mms->streams[i].id);  // stream id
        bytestream_put_le16(&mms->write_out_ptr, 0);                   // selection
    }
    return send_command_packet(mmst);
}