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
 int SOL_16BIT ; 
 int SOL_DPCM ; 

__attribute__((used)) static int sol_codec_type(int magic, int type)
{
    if (magic == 0x0B8D) return 1;//SOL_DPCM_OLD;
    if (type & SOL_DPCM)
    {
        if (type & SOL_16BIT) return 3;//SOL_DPCM_NEW16;
        else if (magic == 0x0C8D) return 1;//SOL_DPCM_OLD;
        else return 2;//SOL_DPCM_NEW8;
    }
    return -1;
}