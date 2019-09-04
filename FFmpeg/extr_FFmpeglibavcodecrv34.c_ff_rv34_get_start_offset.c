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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int* rv34_mb_bits_sizes ; 
 int* rv34_mb_max_sizes ; 

int ff_rv34_get_start_offset(GetBitContext *gb, int mb_size)
{
    int i;
    for(i = 0; i < 5; i++)
        if(rv34_mb_max_sizes[i] >= mb_size - 1)
            break;
    return rv34_mb_bits_sizes[i];
}