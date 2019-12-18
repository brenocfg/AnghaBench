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

/* Variables and functions */
 scalar_t__ have_ts_sync (int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int hb_stream_check_for_ts(const uint8_t *buf)
{
    // transport streams should have a sync byte every 188 bytes.
    // search the first 8KB of buf looking for at least 8 consecutive
    // correctly located sync patterns.
    int offset = 0;
    int count = 16;

    for ( offset = 0; offset < 8*1024-count*188; ++offset )
    {
        if ( have_ts_sync( &buf[offset], 188, count) )
            return 188 | (offset << 8);
        if ( have_ts_sync( &buf[offset], 192, count) )
            return 192 | (offset << 8);
        if ( have_ts_sync( &buf[offset], 204, count) )
            return 204 | (offset << 8);
        if ( have_ts_sync( &buf[offset], 208, count) )
            return 208 | (offset << 8);
    }
    return 0;
}