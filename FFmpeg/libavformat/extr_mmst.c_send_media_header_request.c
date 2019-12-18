#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  write_out_ptr; } ;
struct TYPE_7__ {TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSTContext ;
typedef  TYPE_2__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PKT_MEDIA_HEADER_REQUEST ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insert_command_prefixes (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int send_command_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  start_command_packet (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_media_header_request(MMSTContext *mmst)
{
    MMSContext *mms = &mmst->mms;
    start_command_packet(mmst, CS_PKT_MEDIA_HEADER_REQUEST);
    insert_command_prefixes(mms, 1, 0);
    bytestream_put_le32(&mms->write_out_ptr, 0);
    bytestream_put_le32(&mms->write_out_ptr, 0x00800000);
    bytestream_put_le32(&mms->write_out_ptr, 0xffffffff);
    bytestream_put_le32(&mms->write_out_ptr, 0);
    bytestream_put_le32(&mms->write_out_ptr, 0);
    bytestream_put_le32(&mms->write_out_ptr, 0);

    // the media preroll value in milliseconds?
    bytestream_put_le32(&mms->write_out_ptr, 0);
    bytestream_put_le32(&mms->write_out_ptr, 0x40AC2000);
    bytestream_put_le32(&mms->write_out_ptr, 2);
    bytestream_put_le32(&mms->write_out_ptr, 0);

    return send_command_packet(mmst);
}