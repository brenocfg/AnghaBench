#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int tablepos; int current_continuity_counter; int reading; int* tablebuf; } ;
struct TYPE_6__ {TYPE_1__ pmt_info; } ;
typedef  TYPE_2__ hb_stream_t ;

/* Variables and functions */
 int decode_program_map (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  hb_log (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int* realloc (int*,int) ; 

__attribute__((used)) static int build_program_map(const uint8_t *buf, hb_stream_t *stream)
{
    // Get adaption header info
    int adapt_len = 0;
    int adaption = (buf[3] & 0x30) >> 4;
    if (adaption == 0)
            return 0;
    else if (adaption == 0x2)
            adapt_len = 184;
    else if (adaption == 0x3)
            adapt_len = buf[4] + 1;
    if (adapt_len > 184)
            return 0;

    // Get payload start indicator
    int start;
    start = (buf[1] & 0x40) != 0;

    // Get pointer length - only valid in packets with a start flag
    int pointer_len = 0;

    if (start)
    {
        pointer_len = buf[4 + adapt_len] + 1;
        stream->pmt_info.tablepos = 0;
    }
    // Get Continuity Counter
    int continuity_counter = buf[3] & 0x0f;
    if (!start && (stream->pmt_info.current_continuity_counter + 1 != continuity_counter))
    {
        hb_log("build_program_map - Continuity Counter %d out of sequence - expected %d", continuity_counter, stream->pmt_info.current_continuity_counter+1);
        return 0;
    }
    stream->pmt_info.current_continuity_counter = continuity_counter;
    stream->pmt_info.reading |= start;

    // Add the payload for this packet to the current buffer
    int amount_to_copy = 184 - adapt_len - pointer_len;
    if (stream->pmt_info.reading && (amount_to_copy > 0))
    {
            stream->pmt_info.tablebuf = realloc(stream->pmt_info.tablebuf, stream->pmt_info.tablepos + amount_to_copy);

            memcpy(stream->pmt_info.tablebuf + stream->pmt_info.tablepos, buf + 4 + adapt_len + pointer_len, amount_to_copy);
            stream->pmt_info.tablepos += amount_to_copy;
    }
    if (stream->pmt_info.tablepos > 3)
    {
        // We have enough to check the section length
        int length;
        length = ((stream->pmt_info.tablebuf[1] << 8) +
                  stream->pmt_info.tablebuf[2]) & 0xFFF;
        if (stream->pmt_info.tablepos > length + 1)
        {
            // We just finished a bunch of packets - parse the program map details
            int decode_ok = 0;
            if (stream->pmt_info.tablebuf[0] == 0x02)
                decode_ok = decode_program_map(stream);
            free(stream->pmt_info.tablebuf);
            stream->pmt_info.tablebuf = NULL;
            stream->pmt_info.tablepos = 0;
            stream->pmt_info.reading = 0;
            if (decode_ok)
                return decode_ok;
        }

    }

    return 0;
}