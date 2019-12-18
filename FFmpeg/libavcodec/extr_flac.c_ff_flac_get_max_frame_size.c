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

/* Variables and functions */

int ff_flac_get_max_frame_size(int blocksize, int ch, int bps)
{
    /* Technically, there is no limit to FLAC frame size, but an encoder
       should not write a frame that is larger than if verbatim encoding mode
       were to be used. */

    int count;

    count = 16;                  /* frame header */
    count += ch * ((7+bps+7)/8); /* subframe headers */
    if (ch == 2) {
        /* for stereo, need to account for using decorrelation */
        count += (( 2*bps+1) * blocksize + 7) / 8;
    } else {
        count += ( ch*bps    * blocksize + 7) / 8;
    }
    count += 2; /* frame footer */

    return count;
}