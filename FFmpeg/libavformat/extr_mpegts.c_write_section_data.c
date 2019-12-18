#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {int* crc_validity; } ;
struct TYPE_9__ {int* section_buf; int section_index; int section_h_size; int end_of_section_reached; int last_ver; int /*<<< orphan*/  (* section_cb ) (TYPE_3__*,int*,int) ;int /*<<< orphan*/  crc; scalar_t__ check_crc; } ;
struct TYPE_8__ {TYPE_2__ section_filter; } ;
struct TYPE_10__ {size_t pid; TYPE_1__ u; } ;
typedef  TYPE_2__ MpegTSSectionFilter ;
typedef  TYPE_3__ MpegTSFilter ;
typedef  TYPE_4__ MpegTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CRC_32_IEEE ; 
 int AV_RB16 (int*) ; 
 int /*<<< orphan*/  AV_RB32 (int*) ; 
 int MAX_SECTION_SIZE ; 
 int /*<<< orphan*/  av_crc (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int*,int) ; 

__attribute__((used)) static void write_section_data(MpegTSContext *ts, MpegTSFilter *tss1,
                               const uint8_t *buf, int buf_size, int is_start)
{
    MpegTSSectionFilter *tss = &tss1->u.section_filter;
    uint8_t *cur_section_buf = NULL;
    int len, offset;

    if (is_start) {
        memcpy(tss->section_buf, buf, buf_size);
        tss->section_index = buf_size;
        tss->section_h_size = -1;
        tss->end_of_section_reached = 0;
    } else {
        if (tss->end_of_section_reached)
            return;
        len = MAX_SECTION_SIZE - tss->section_index;
        if (buf_size < len)
            len = buf_size;
        memcpy(tss->section_buf + tss->section_index, buf, len);
        tss->section_index += len;
    }

    offset = 0;
    cur_section_buf = tss->section_buf;
    while (cur_section_buf - tss->section_buf < MAX_SECTION_SIZE && cur_section_buf[0] != 0xff) {
        /* compute section length if possible */
        if (tss->section_h_size == -1 && tss->section_index - offset >= 3) {
            len = (AV_RB16(cur_section_buf + 1) & 0xfff) + 3;
            if (len > MAX_SECTION_SIZE)
                return;
            tss->section_h_size = len;
        }

        if (tss->section_h_size != -1 &&
            tss->section_index >= offset + tss->section_h_size) {
            int crc_valid = 1;
            tss->end_of_section_reached = 1;

            if (tss->check_crc) {
                crc_valid = !av_crc(av_crc_get_table(AV_CRC_32_IEEE), -1, cur_section_buf, tss->section_h_size);
                if (tss->section_h_size >= 4)
                    tss->crc = AV_RB32(cur_section_buf + tss->section_h_size - 4);

                if (crc_valid) {
                    ts->crc_validity[ tss1->pid ] = 100;
                }else if (ts->crc_validity[ tss1->pid ] > -10) {
                    ts->crc_validity[ tss1->pid ]--;
                }else
                    crc_valid = 2;
            }
            if (crc_valid) {
                tss->section_cb(tss1, cur_section_buf, tss->section_h_size);
                if (crc_valid != 1)
                    tss->last_ver = -1;
            }

            cur_section_buf += tss->section_h_size;
            offset += tss->section_h_size;
            tss->section_h_size = -1;
        } else {
            tss->section_h_size = -1;
            tss->end_of_section_reached = 0;
            break;
        }
    }
}