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
struct TYPE_5__ {TYPE_1__* frame; } ;
struct TYPE_4__ {int* linesize; } ;
typedef  TYPE_2__ SeqVideoContext ;

/* Variables and functions */

__attribute__((used)) static const unsigned char *seq_decode_op3(SeqVideoContext *seq,
                                           const unsigned char *src,
                                           const unsigned char *src_end,
                                           unsigned char *dst)
{
    int pos, offset;

    do {
        if (src_end - src < 2)
            return NULL;
        pos = *src++;
        offset = ((pos >> 3) & 7) * seq->frame->linesize[0] + (pos & 7);
        dst[offset] = *src++;
    } while (!(pos & 0x80));

    return src;
}