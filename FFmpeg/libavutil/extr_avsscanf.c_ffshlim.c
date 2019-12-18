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
typedef  scalar_t__ ptrdiff_t ;
struct TYPE_3__ {scalar_t__ rend; scalar_t__ shend; scalar_t__ rpos; scalar_t__ buf; scalar_t__ shcnt; scalar_t__ shlim; } ;
typedef  TYPE_1__ FFFILE ;

/* Variables and functions */

__attribute__((used)) static void ffshlim(FFFILE *f, ptrdiff_t lim)
{
    f->shlim = lim;
    f->shcnt = f->buf - f->rpos;
    /* If lim is nonzero, rend must be a valid pointer. */
    if (lim && f->rend - f->rpos > lim)
        f->shend = f->rpos + lim;
    else
        f->shend = f->rend;
}