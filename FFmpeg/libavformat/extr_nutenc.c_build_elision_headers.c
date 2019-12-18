#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; } ;
typedef  TYPE_1__ uint8_t ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {int header_count; TYPE_1__ const** header; TYPE_1__* header_len; } ;
typedef  TYPE_2__ NUTContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static void build_elision_headers(AVFormatContext *s)
{
    NUTContext *nut = s->priv_data;
    int i;
    //FIXME this is lame
    //FIXME write a 2pass mode to find the maximal headers
    static const uint8_t headers[][5] = {
        { 3, 0x00, 0x00, 0x01 },
        { 4, 0x00, 0x00, 0x01, 0xB6},
        { 2, 0xFF, 0xFA }, //mp3+crc
        { 2, 0xFF, 0xFB }, //mp3
        { 2, 0xFF, 0xFC }, //mp2+crc
        { 2, 0xFF, 0xFD }, //mp2
    };

    nut->header_count = 7;
    for (i = 1; i < nut->header_count; i++) {
        nut->header_len[i] = headers[i - 1][0];
        nut->header[i]     = &headers[i - 1][1];
    }
}