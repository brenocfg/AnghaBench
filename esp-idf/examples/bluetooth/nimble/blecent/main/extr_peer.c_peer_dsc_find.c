#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ handle; } ;
struct peer_dsc {TYPE_1__ dsc; } ;
struct peer_chr {int /*<<< orphan*/  dscs; } ;

/* Variables and functions */
 struct peer_dsc* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct peer_dsc* SLIST_NEXT (struct peer_dsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 struct peer_dsc* peer_dsc_find_prev (struct peer_chr const*,scalar_t__) ; 

__attribute__((used)) static struct peer_dsc *
peer_dsc_find(const struct peer_chr *chr, uint16_t dsc_handle,
              struct peer_dsc **out_prev)
{
    struct peer_dsc *prev;
    struct peer_dsc *dsc;

    prev = peer_dsc_find_prev(chr, dsc_handle);
    if (prev == NULL) {
        dsc = SLIST_FIRST(&chr->dscs);
    } else {
        dsc = SLIST_NEXT(prev, next);
    }

    if (dsc != NULL && dsc->dsc.handle != dsc_handle) {
        dsc = NULL;
    }

    if (out_prev != NULL) {
        *out_prev = prev;
    }
    return dsc;
}