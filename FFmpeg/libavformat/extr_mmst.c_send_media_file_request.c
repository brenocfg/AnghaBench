#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  write_out_ptr; } ;
struct TYPE_8__ {scalar_t__ path; TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSTContext ;
typedef  TYPE_2__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PKT_MEDIA_FILE_REQUEST ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_command_prefixes (TYPE_2__*,int,int) ; 
 int mms_put_utf16 (TYPE_2__*,scalar_t__) ; 
 int send_command_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  start_command_packet (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_media_file_request(MMSTContext *mmst)
{
    int ret;
    MMSContext *mms = &mmst->mms;
    start_command_packet(mmst, CS_PKT_MEDIA_FILE_REQUEST);
    insert_command_prefixes(mms, 1, 0xffffffff);
    bytestream_put_le32(&mms->write_out_ptr, 0);
    bytestream_put_le32(&mms->write_out_ptr, 0);
    if ((ret = mms_put_utf16(mms, mmst->path + 1)) < 0) // +1 for skip "/"
        return ret;

    return send_command_packet(mmst);
}