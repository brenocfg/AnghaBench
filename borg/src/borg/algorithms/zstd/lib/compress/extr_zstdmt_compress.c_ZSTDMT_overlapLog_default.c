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
typedef  int ZSTD_strategy ;

/* Variables and functions */
#define  ZSTD_btlazy2 136 
#define  ZSTD_btopt 135 
#define  ZSTD_btultra 134 
#define  ZSTD_btultra2 133 
#define  ZSTD_dfast 132 
#define  ZSTD_fast 131 
#define  ZSTD_greedy 130 
#define  ZSTD_lazy 129 
#define  ZSTD_lazy2 128 

__attribute__((used)) static int ZSTDMT_overlapLog_default(ZSTD_strategy strat)
{
    switch(strat)
    {
        case ZSTD_btultra2:
            return 9;
        case ZSTD_btultra:
        case ZSTD_btopt:
            return 8;
        case ZSTD_btlazy2:
        case ZSTD_lazy2:
            return 7;
        case ZSTD_lazy:
        case ZSTD_greedy:
        case ZSTD_dfast:
        case ZSTD_fast:
        default:;
    }
    return 6;
}