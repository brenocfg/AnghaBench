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
 int /*<<< orphan*/  av_assert0 (int) ; 
 int* ff_flac_blocksize_table ; 

__attribute__((used)) static int select_blocksize(int samplerate, int block_time_ms)
{
    int i;
    int target;
    int blocksize;

    av_assert0(samplerate > 0);
    blocksize = ff_flac_blocksize_table[1];
    target    = (samplerate * block_time_ms) / 1000;
    for (i = 0; i < 16; i++) {
        if (target >= ff_flac_blocksize_table[i] &&
            ff_flac_blocksize_table[i] > blocksize) {
            blocksize = ff_flac_blocksize_table[i];
        }
    }
    return blocksize;
}