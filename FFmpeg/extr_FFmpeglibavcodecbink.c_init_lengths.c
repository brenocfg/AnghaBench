#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* bundle; } ;
struct TYPE_4__ {void* len; } ;
typedef  TYPE_2__ BinkContext ;

/* Variables and functions */
 size_t BINK_SRC_BLOCK_TYPES ; 
 size_t BINK_SRC_COLORS ; 
 size_t BINK_SRC_INTER_DC ; 
 size_t BINK_SRC_INTRA_DC ; 
 size_t BINK_SRC_PATTERN ; 
 size_t BINK_SRC_RUN ; 
 size_t BINK_SRC_SUB_BLOCK_TYPES ; 
 size_t BINK_SRC_X_OFF ; 
 size_t BINK_SRC_Y_OFF ; 
 int FFALIGN (int,int) ; 
 void* av_log2 (int) ; 

__attribute__((used)) static void init_lengths(BinkContext *c, int width, int bw)
{
    width = FFALIGN(width, 8);

    c->bundle[BINK_SRC_BLOCK_TYPES].len = av_log2((width >> 3) + 511) + 1;

    c->bundle[BINK_SRC_SUB_BLOCK_TYPES].len = av_log2((width >> 4) + 511) + 1;

    c->bundle[BINK_SRC_COLORS].len = av_log2(bw*64 + 511) + 1;

    c->bundle[BINK_SRC_INTRA_DC].len =
    c->bundle[BINK_SRC_INTER_DC].len =
    c->bundle[BINK_SRC_X_OFF].len =
    c->bundle[BINK_SRC_Y_OFF].len = av_log2((width >> 3) + 511) + 1;

    c->bundle[BINK_SRC_PATTERN].len = av_log2((bw << 3) + 511) + 1;

    c->bundle[BINK_SRC_RUN].len = av_log2(bw*48 + 511) + 1;
}