#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ end_handle; } ;
struct peer_svc {TYPE_2__ svc; } ;
struct TYPE_3__ {scalar_t__ def_handle; } ;
struct peer_chr {TYPE_1__ chr; } ;

/* Variables and functions */
 struct peer_chr* SLIST_NEXT (struct peer_chr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

uint16_t
chr_end_handle(const struct peer_svc *svc, const struct peer_chr *chr)
{
    const struct peer_chr *next_chr;

    next_chr = SLIST_NEXT(chr, next);
    if (next_chr != NULL) {
        return next_chr->chr.def_handle - 1;
    } else {
        return svc->svc.end_handle;
    }
}