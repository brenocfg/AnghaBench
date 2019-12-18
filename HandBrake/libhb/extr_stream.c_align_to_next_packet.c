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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int off_t ;
struct TYPE_3__ {int packetsize; int /*<<< orphan*/  file_handle; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ hb_stream_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HB_ERROR_READ ; 
 int MAX_HOLE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int ferror (int /*<<< orphan*/ ) ; 
 int fread (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ftello (int /*<<< orphan*/ ) ; 
 scalar_t__ have_ts_sync (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  hb_error (char*,int) ; 
 int /*<<< orphan*/  hb_set_work_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t align_to_next_packet(hb_stream_t *stream)
{
    uint8_t buf[MAX_HOLE];
    off_t pos = 0;
    off_t start = ftello(stream->file_handle);
    off_t orig;

    if ( start >= stream->packetsize ) {
        start -= stream->packetsize;
        fseeko(stream->file_handle, start, SEEK_SET);
    }
    orig = start;

    while (1)
    {
        if (fread(buf, sizeof(buf), 1, stream->file_handle) == 1)
        {
            const uint8_t *bp = buf;
            int i;

            for ( i = sizeof(buf) - 8 * stream->packetsize; --i >= 0; ++bp )
            {
                if ( have_ts_sync( bp, stream->packetsize, 8 ) )
                {
                    break;
                }
            }
            if ( i >= 0 )
            {
                pos = ( bp - buf ) - stream->packetsize + 188;
                break;
            }
            fseeko(stream->file_handle, -8 * stream->packetsize, SEEK_CUR);
            start = ftello(stream->file_handle);
        }
        else
        {
            int err;
            if ((err = ferror(stream->file_handle)) != 0)
            {
                hb_error("align_to_next_packet: error (%d)", err);
                hb_set_work_error(stream->h, HB_ERROR_READ);
            }
            return 0;
        }
    }
    fseeko(stream->file_handle, start+pos, SEEK_SET);
    return start - orig + pos;
}