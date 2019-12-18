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
struct TYPE_3__ {scalar_t__ q_scale_type; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int* ff_mpeg2_non_linear_qscale ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int mpeg_get_qscale(MpegEncContext *s)
{
    int qscale = get_bits(&s->gb, 5);
    if (s->q_scale_type)
        return ff_mpeg2_non_linear_qscale[qscale];
    else
        return qscale << 1;
}