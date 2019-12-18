#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  hb_stream_t ;
struct TYPE_14__ {int stream_id; int packet_len; int header_len; void* dts; void* pts; } ;
typedef  TYPE_1__ hb_pes_info_t ;
struct TYPE_15__ {int pos; } ;
typedef  TYPE_2__ bitbuf_t ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 int bits_bytes_left (TYPE_2__*) ; 
 int /*<<< orphan*/  bits_clone (TYPE_2__*,TYPE_2__*,int) ; 
 int bits_get (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bits_init (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int parse_pack_header (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int parse_pes_header (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int hb_parse_ps(
    hb_stream_t   *stream,
    uint8_t       *buf,
    int           len,
    hb_pes_info_t *pes_info )
{
    memset( pes_info, 0, sizeof( hb_pes_info_t ) );
    pes_info->pts = AV_NOPTS_VALUE;
    pes_info->dts = AV_NOPTS_VALUE;

    bitbuf_t bb, cc;
    bits_init(&bb, buf, len, 0);
    bits_clone(&cc, &bb, len);

    if ( bits_bytes_left(&bb) < 4 )
        return 0;

    // Validate start code
    if ( bits_get(&bb, 8 * 3) != 0x000001 )
    {
        return 0;
    }

    pes_info->stream_id = bits_get(&bb, 8);
    if ( pes_info->stream_id == 0xb9 )
    {
        // Program stream end code
        return 1;
    }
    else if ( pes_info->stream_id == 0xba )
    {
        return parse_pack_header( stream, &cc, pes_info );
    }
    else if ( pes_info->stream_id >= 0xbd &&
              pes_info->stream_id != 0xbe &&
              pes_info->stream_id != 0xbf &&
              pes_info->stream_id != 0xf0 &&
              pes_info->stream_id != 0xf1 &&
              pes_info->stream_id != 0xf2 &&
              pes_info->stream_id != 0xf8 &&
              pes_info->stream_id != 0xff )
    {
        return parse_pes_header( stream, &cc, pes_info );
    }
    else
    {
        if ( bits_bytes_left(&bb) < 2 )
        {
            return 0;
        }
        pes_info->packet_len = bits_get(&bb, 16);
        pes_info->header_len = bb.pos >> 3;
        return 1;
    }
}