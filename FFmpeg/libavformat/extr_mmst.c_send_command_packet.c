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
struct TYPE_5__ {int write_out_ptr; int out_buffer; int /*<<< orphan*/  mms_hd; } ;
struct TYPE_4__ {TYPE_2__ mms; } ;
typedef  TYPE_1__ MMSTContext ;
typedef  TYPE_2__ MMSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVUNERROR (int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WL32 (int,int) ; 
 int /*<<< orphan*/  EIO ; 
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int ffurl_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_command_packet(MMSTContext *mmst)
{
    MMSContext *mms  = &mmst->mms;
    int len= mms->write_out_ptr - mms->out_buffer;
    int exact_length = FFALIGN(len, 8);
    int first_length= exact_length - 16;
    int len8= first_length/8;
    int write_result;

    // update packet length fields.
    AV_WL32(mms->out_buffer + 8, first_length);
    AV_WL32(mms->out_buffer + 16, len8);
    AV_WL32(mms->out_buffer + 32, len8-2);
    memset(mms->write_out_ptr, 0, exact_length - len);

    // write it out.
    write_result= ffurl_write(mms->mms_hd, mms->out_buffer, exact_length);
    if(write_result != exact_length) {
        av_log(mms->mms_hd, AV_LOG_ERROR,
               "Failed to write data of length %d: %d (%s)\n",
               exact_length, write_result,
               write_result < 0 ? strerror(AVUNERROR(write_result)) :
                   "The server closed the connection");
        return AVERROR(EIO);
    }

    return 0;
}