#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  hb_stream_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/ * flush_ts_streams (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/ * hb_ts_decode_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * next_packet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_buffer_t * hb_ts_stream_decode( hb_stream_t *stream )
{
    hb_buffer_t * b;

    // spin until we get a packet of data from some stream or hit eof
    while ( 1 )
    {
        const uint8_t *buf = next_packet(stream);
        if ( buf == NULL )
        {
            // end of file - we didn't finish filling our ps write buffer
            // so just discard the remainder (the partial buffer is useless)
            hb_log("hb_ts_stream_decode - eof");
            b = flush_ts_streams(stream);
            return b;
        }

        b = hb_ts_decode_pkt( stream, buf, 0, 0 );
        if ( b )
        {
            return b;
        }
    }
    return NULL;
}