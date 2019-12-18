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
struct TYPE_8__ {char* host; TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSTContext ;
typedef  TYPE_2__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PKT_INITIAL ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insert_command_prefixes (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int mms_put_utf16 (TYPE_2__*,char*) ; 
 int send_command_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  start_command_packet (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_startup_packet(MMSTContext *mmst)
{
    char data_string[256];
    int ret;
    MMSContext *mms = &mmst->mms;
    // SubscriberName is defined in MS specification linked below.
    // The GUID value can be any valid value.
    // http://download.microsoft.com/
    // download/9/5/E/95EF66AF-9026-4BB0-A41D-A4F81802D92C/%5BMS-WMSP%5D.pdf
    snprintf(data_string, sizeof(data_string),
            "NSPlayer/7.0.0.1956; {%s}; Host: %s",
            "7E667F5D-A661-495E-A512-F55686DDA178", mmst->host);

    start_command_packet(mmst, CS_PKT_INITIAL);
    insert_command_prefixes(mms, 0, 0x0004000b);
    bytestream_put_le32(&mms->write_out_ptr, 0x0003001c);
    if ((ret = mms_put_utf16(mms, data_string)) < 0)
        return ret;
    return send_command_packet(mmst);
}