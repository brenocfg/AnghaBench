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
struct TYPE_10__ {TYPE_2__* list; } ;
struct TYPE_8__ {void* PCR_PID; int /*<<< orphan*/  tablepos; int /*<<< orphan*/  tablebuf; } ;
struct TYPE_11__ {TYPE_3__ pes; void* reg_desc; TYPE_1__ pmt_info; } ;
typedef  TYPE_4__ hb_stream_t ;
typedef  int /*<<< orphan*/  bitbuf_t ;
struct TYPE_9__ {int map_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  bits_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 void* bits_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bits_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bits_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_element_descriptors (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_ts_streams (TYPE_4__*,unsigned int,int /*<<< orphan*/ ,unsigned char,int,int*) ; 

int decode_program_map(hb_stream_t* stream)
{
    bitbuf_t bb;
    bits_init(&bb, stream->pmt_info.tablebuf, stream->pmt_info.tablepos, 0);

    bits_get(&bb, 8);  // table_id
    bits_get(&bb, 4);
    unsigned int section_length = bits_get(&bb, 12);

    bits_get(&bb, 16); // program number
    bits_get(&bb, 2);
    bits_get(&bb, 5);  // version_number
    bits_get(&bb, 1);
    bits_get(&bb, 8);  // section_number
    bits_get(&bb, 8);  // last_section_number
    bits_get(&bb, 3);
    stream->pmt_info.PCR_PID = bits_get(&bb, 13);
    bits_get(&bb, 4);
    int program_info_length = bits_get(&bb, 12);
    int i;
    for (i = 0; i < program_info_length - 2; )
    {
        uint8_t tag, len;
        tag = bits_get(&bb, 8);
        len = bits_get(&bb, 8);
        i += 2;
        if ( i + len > program_info_length )
        {
            break;
        }
        if (tag == 0x05 && len >= 4)
        {
            // registration descriptor
            stream->reg_desc = bits_get(&bb, 32);
            i += 4;
            len -= 4;
        }
        int j;
        for ( j = 0; j < len; j++ )
        {
            bits_get(&bb, 8);
        }
        i += len;
    }
    for ( ; i < program_info_length; i++ )
    {
        bits_get(&bb, 8);
    }

    int cur_pos =  9 /* data after the section length field*/ + program_info_length;
    int done_reading_stream_types = 0;
    int ii = 0;
    while (!done_reading_stream_types)
    {
        unsigned char stream_type = bits_get(&bb, 8);
        bits_get(&bb, 3);
        unsigned int elementary_PID = bits_get(&bb, 13);
        bits_get(&bb, 4);
        unsigned int info_len = bits_get(&bb, 12);
        // Defined audio stream types are 0x81 for AC-3/A52 audio
        // and 0x03 for mpeg audio. But content producers seem to
        // use other values (0x04 and 0x06 have both been observed)
        // so at this point we say everything that isn't a video
        // pid is audio then at the end of hb_stream_title_scan
        // we'll figure out which are really audio by looking at
        // the PES headers.
        int pes_idx;
        update_ts_streams( stream, elementary_PID, 0,
                           stream_type, -1, &pes_idx );
        if ( pes_idx >= 0 )
            stream->pes.list[pes_idx].map_idx = ii;
        if (info_len > 0)
        {
            bitbuf_t bb_desc;
            bits_clone( &bb_desc, &bb, info_len );
            if ( pes_idx >= 0 )
                decode_element_descriptors( stream, pes_idx, &bb_desc );
            bits_skip(&bb, 8 * info_len);
        }

        cur_pos += 5 /* stream header */ + info_len;

        if (cur_pos >= section_length - 4 /* stop before the CRC */)
            done_reading_stream_types = 1;
        ii++;
    }

    return 1;
}