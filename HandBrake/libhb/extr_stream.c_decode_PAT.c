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
typedef  int uint8_t ;
struct TYPE_5__ {size_t ts_number_pat_entries; TYPE_1__* pat_info; } ;
typedef  TYPE_2__ hb_stream_t ;
typedef  int /*<<< orphan*/  bitbuf_t ;
struct TYPE_4__ {unsigned int program_number; unsigned int program_map_PID; } ;

/* Variables and functions */
 void* bits_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bits_init (int /*<<< orphan*/ *,unsigned char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 size_t kMaxNumberPMTStreams ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int const*,int) ; 

__attribute__((used)) static int decode_PAT(const uint8_t *buf, hb_stream_t *stream)
{
    unsigned char tablebuf[1024];
    unsigned int tablepos = 0;

    int reading = 0;


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

    // Get pointer length
    int pointer_len = buf[4 + adapt_len] + 1;

    // Get payload start indicator
    int start;
    start = (buf[1] & 0x40) != 0;

    if (start)
            reading = 1;

    // Add the payload for this packet to the current buffer
    if (reading && (184 - adapt_len) > 0)
    {
            if (tablepos + 184 - adapt_len - pointer_len > 1024)
            {
                    hb_log("decode_PAT - Bad program section length (> 1024)");
                    return 0;
            }
            memcpy(tablebuf + tablepos, buf + 4 + adapt_len + pointer_len, 184 - adapt_len - pointer_len);
            tablepos += 184 - adapt_len - pointer_len;
    }

    if (start && reading)
    {
            memcpy(tablebuf + tablepos, buf + 4 + adapt_len + 1, pointer_len - 1);


            unsigned int pos = 0;
            //while (pos < tablepos)
            {
                    bitbuf_t bb;
                    bits_init(&bb, tablebuf + pos, tablepos - pos, 0);

                    unsigned char section_id    = bits_get(&bb, 8);
                    bits_get(&bb, 4);
                    unsigned int section_len    = bits_get(&bb, 12);
                    bits_get(&bb, 16); // transport_id
                    bits_get(&bb, 2);
                    bits_get(&bb, 5);  // version_num
                    bits_get(&bb, 1);  // current_next
                    bits_get(&bb, 8);  // section_num
                    bits_get(&bb, 8);  // last_section

                    switch (section_id)
                    {
                      case 0x00:
                        {
                          // Program Association Section
                          section_len -= 5;    // Already read transport stream ID, version num, section num, and last section num
                          section_len -= 4;   // Ignore the CRC
                          int curr_pos = 0;
                          stream->ts_number_pat_entries = 0;
                          while ((curr_pos < section_len) && (stream->ts_number_pat_entries < kMaxNumberPMTStreams))
                          {
                            unsigned int pkt_program_num = bits_get(&bb, 16);
                            stream->pat_info[stream->ts_number_pat_entries].program_number = pkt_program_num;

                            bits_get(&bb, 3);  // Reserved
                            if (pkt_program_num == 0)
                            {
                              bits_get(&bb, 13); // pkt_network_id
                            }
                            else
                            {
                              unsigned int pkt_program_map_PID = bits_get(&bb, 13);
                                stream->pat_info[stream->ts_number_pat_entries].program_map_PID = pkt_program_map_PID;
                            }
                            curr_pos += 4;
                            stream->ts_number_pat_entries++;
                          }
                        }
                        break;
                      case 0xC7:
                            {
                                    break;
                            }
                      case 0xC8:
                            {
                                    break;
                            }
                    }

//                    pos += 3 + section_len;
            }

//            tablepos = 0;
    }
    return 1;
}