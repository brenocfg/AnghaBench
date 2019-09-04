#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int** mpeg_f_code; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static inline int mpeg2_get_f_code(const MpegEncContext *s)
{
    return (s->mpeg_f_code[0][0] << 12) | (s->mpeg_f_code[0][1] << 8) |
           (s->mpeg_f_code[1][0] <<  4) |  s->mpeg_f_code[1][1];
}