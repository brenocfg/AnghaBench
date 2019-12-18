#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ remaining_in_len; scalar_t__ asf_packet_len; int in_buffer; } ;
typedef  TYPE_1__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pad_media_packet(MMSContext *mms)
{
    if(mms->remaining_in_len<mms->asf_packet_len) {
        int padding_size = mms->asf_packet_len - mms->remaining_in_len;
        memset(mms->in_buffer + mms->remaining_in_len, 0, padding_size);
        mms->remaining_in_len += padding_size;
    }
}