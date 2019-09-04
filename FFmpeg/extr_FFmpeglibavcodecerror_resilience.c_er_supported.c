#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ field_picture; int /*<<< orphan*/  f; } ;
struct TYPE_9__ {TYPE_3__ cur_pic; TYPE_2__* avctx; } ;
struct TYPE_7__ {TYPE_1__* hwaccel; } ;
struct TYPE_6__ {scalar_t__ decode_slice; } ;
typedef  TYPE_4__ ERContext ;

/* Variables and functions */

__attribute__((used)) static int er_supported(ERContext *s)
{
    if(s->avctx->hwaccel && s->avctx->hwaccel->decode_slice           ||
       !s->cur_pic.f                                                  ||
       s->cur_pic.field_picture
    )
        return 0;
    return 1;
}