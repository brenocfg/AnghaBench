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
 int avpriv_codec2_mode_block_align (void*,int) ; 
 int avpriv_codec2_mode_frame_size (void*,int) ; 

int avpriv_codec2_mode_bit_rate(void *logctx, int mode)
{
    int frame_size  = avpriv_codec2_mode_frame_size(logctx, mode);
    int block_align = avpriv_codec2_mode_block_align(logctx, mode);

    if (frame_size <= 0 || block_align <= 0) {
        return 0;
    }

    return 8 * 8000 * block_align / frame_size;
}