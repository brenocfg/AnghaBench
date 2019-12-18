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
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  file_handle; } ;
typedef  TYPE_1__ hb_stream_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ check_ps_sc (int*) ; 
 scalar_t__ check_ps_sync (int*) ; 
 int fread (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hb_stream_check_for_ps(hb_stream_t *stream)
{
    uint8_t buf[2048*4];
    uint8_t sc_buf[4];
    int pos = 0;

    fseek(stream->file_handle, 0, SEEK_SET);

    // program streams should start with a PACK then some other mpeg start
    // code (usually a SYS but that might be missing if we only have a clip).
    while (pos < 512 * 1024)
    {
        int offset;

        if ( fread(buf, 1, sizeof(buf), stream->file_handle) != sizeof(buf) )
            return 0;

        for ( offset = 0; offset < 8*1024-27; ++offset )
        {
            if ( check_ps_sync( &buf[offset] ) && check_ps_sc( &buf[offset] ) )
            {
                int pes_offset, prev, data_len;
                uint8_t sid;
                uint8_t *b = buf+offset;

                // Skip the pack header
                int mark = buf[4] >> 4;
                if ( mark == 0x02 )
                {
                    // mpeg-1 pack header
                    pes_offset = 12;
                }
                else
                {
                    // mpeg-2 pack header
                    pes_offset = 14 + ( buf[13] & 0x7 );
                }

                b +=  pes_offset;
                // Get the next stream id
                sid = b[3];
                data_len = (b[4] << 8) + b[5];
                if ( data_len && sid > 0xba && sid < 0xf9 )
                {
                    prev = ftell( stream->file_handle );
                    pos = prev - ( sizeof(buf) - offset );
                    pos += pes_offset + 6 + data_len;
                    fseek( stream->file_handle, pos, SEEK_SET );
                    if ( fread(sc_buf, 1, 4, stream->file_handle) != 4 )
                        return 0;
                    if (sc_buf[0] == 0x00 && sc_buf[1] == 0x00 &&
                        sc_buf[2] == 0x01)
                    {
                        return 1;
                    }
                    fseek( stream->file_handle, prev, SEEK_SET );
                }
            }
        }
        fseek( stream->file_handle, -27, SEEK_CUR );
        pos = ftell( stream->file_handle );
    }
    return 0;
}