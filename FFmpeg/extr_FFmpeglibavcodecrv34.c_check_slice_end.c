#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ mb_y; scalar_t__ mb_height; int /*<<< orphan*/  gb; int /*<<< orphan*/  mb_num_left; } ;
struct TYPE_6__ {int mb_skip_run; } ;
struct TYPE_7__ {TYPE_1__ s; } ;
typedef  TYPE_2__ RV34DecContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int check_slice_end(RV34DecContext *r, MpegEncContext *s)
{
    int bits;
    if(s->mb_y >= s->mb_height)
        return 1;
    if(!s->mb_num_left)
        return 1;
    if(r->s.mb_skip_run > 1)
        return 0;
    bits = get_bits_left(&s->gb);
    if(bits <= 0 || (bits < 8 && !show_bits(&s->gb, bits)))
        return 1;
    return 0;
}