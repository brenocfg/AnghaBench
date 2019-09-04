#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {scalar_t__ chroma_format; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ CHROMA_420 ; 
 int /*<<< orphan*/  mpeg1_encode_mb_internal (TYPE_1__*,int /*<<< orphan*/ **,int,int,int) ; 

void ff_mpeg1_encode_mb(MpegEncContext *s, int16_t block[8][64],
                        int motion_x, int motion_y)
{
    if (s->chroma_format == CHROMA_420)
        mpeg1_encode_mb_internal(s, block, motion_x, motion_y, 6);
    else
        mpeg1_encode_mb_internal(s, block, motion_x, motion_y, 8);
}