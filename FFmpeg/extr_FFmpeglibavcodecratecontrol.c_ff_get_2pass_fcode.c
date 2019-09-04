#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* entry; } ;
struct TYPE_7__ {size_t picture_number; int /*<<< orphan*/  b_code; int /*<<< orphan*/  f_code; TYPE_2__ rc_context; } ;
struct TYPE_5__ {int /*<<< orphan*/  b_code; int /*<<< orphan*/  f_code; } ;
typedef  TYPE_1__ RateControlEntry ;
typedef  TYPE_2__ RateControlContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */

void ff_get_2pass_fcode(MpegEncContext *s)
{
    RateControlContext *rcc = &s->rc_context;
    RateControlEntry *rce   = &rcc->entry[s->picture_number];

    s->f_code = rce->f_code;
    s->b_code = rce->b_code;
}