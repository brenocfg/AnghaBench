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
typedef  int /*<<< orphan*/  data_string ;
struct TYPE_9__ {int /*<<< orphan*/  write_out_ptr; } ;
struct TYPE_8__ {TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSTContext ;
typedef  TYPE_2__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PKT_PROTOCOL_SELECT ; 
 int LOCAL_ADDRESS ; 
 int LOCAL_PORT ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insert_command_prefixes (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int mms_put_utf16 (TYPE_2__*,char*) ; 
 int send_command_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,char*,int) ; 
 int /*<<< orphan*/  start_command_packet (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_protocol_select(MMSTContext *mmst)
{
    int ret;
    char data_string[256];
    MMSContext *mms = &mmst->mms;

    start_command_packet(mmst, CS_PKT_PROTOCOL_SELECT);
    insert_command_prefixes(mms, 0, 0xffffffff);
    bytestream_put_le32(&mms->write_out_ptr, 0);          // maxFunnelBytes
    bytestream_put_le32(&mms->write_out_ptr, 0x00989680); // maxbitRate
    bytestream_put_le32(&mms->write_out_ptr, 2);          // funnelMode
    snprintf(data_string, sizeof(data_string), "\\\\%d.%d.%d.%d\\%s\\%d",
            (LOCAL_ADDRESS>>24)&0xff,
            (LOCAL_ADDRESS>>16)&0xff,
            (LOCAL_ADDRESS>>8)&0xff,
            LOCAL_ADDRESS&0xff,
            "TCP",                                        // or UDP
            LOCAL_PORT);

    if ((ret = mms_put_utf16(mms, data_string)) < 0)
        return ret;
    return send_command_packet(mmst);
}