#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int channels; } ;
typedef  TYPE_1__ FlacEncodeContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int INT_MAX ; 
 int count_frame_header (TYPE_1__*) ; 
 scalar_t__ encode_residual_ch (TYPE_1__*,int) ; 

__attribute__((used)) static int encode_frame(FlacEncodeContext *s)
{
    int ch;
    uint64_t count;

    count = count_frame_header(s);

    for (ch = 0; ch < s->channels; ch++)
        count += encode_residual_ch(s, ch);

    count += (8 - (count & 7)) & 7; // byte alignment
    count += 16;                    // CRC-16

    count >>= 3;
    if (count > INT_MAX)
        return AVERROR_BUG;
    return count;
}