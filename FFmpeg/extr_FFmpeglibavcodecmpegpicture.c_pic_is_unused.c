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
struct TYPE_5__ {int reference; scalar_t__ needs_realloc; TYPE_1__* f; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__ Picture ;

/* Variables and functions */
 int DELAYED_PIC_REF ; 

__attribute__((used)) static inline int pic_is_unused(Picture *pic)
{
    if (!pic->f->buf[0])
        return 1;
    if (pic->needs_realloc && !(pic->reference & DELAYED_PIC_REF))
        return 1;
    return 0;
}