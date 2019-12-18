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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  file_handle; } ;
typedef  TYPE_1__ hb_stream_t ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ ) ; 
 int getc_unlocked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skip_to_next_pack( hb_stream_t *src_stream )
{
    // scan forward until we find the start of the next pack
    uint32_t strt_code = -1;
    int c;

    flockfile( src_stream->file_handle );
    while ( ( c = getc_unlocked( src_stream->file_handle ) ) != EOF )
    {
        strt_code = ( strt_code << 8 ) | c;
        if ( strt_code == 0x000001ba )
            // we found the start of the next pack
            break;
    }
    funlockfile( src_stream->file_handle );

    // if we didn't terminate on an eof back up so the next read
    // starts on the pack boundary.
    if ( c != EOF )
    {
        fseeko( src_stream->file_handle, -4, SEEK_CUR );
    }
}