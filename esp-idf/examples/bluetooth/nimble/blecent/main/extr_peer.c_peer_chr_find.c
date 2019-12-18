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
struct peer_svc {int /*<<< orphan*/  chrs; } ;
struct TYPE_2__ {scalar_t__ val_handle; } ;
struct peer_chr {TYPE_1__ chr; } ;

/* Variables and functions */
 struct peer_chr* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct peer_chr* SLIST_NEXT (struct peer_chr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 struct peer_chr* peer_chr_find_prev (struct peer_svc const*,scalar_t__) ; 

__attribute__((used)) static struct peer_chr *
peer_chr_find(const struct peer_svc *svc, uint16_t chr_val_handle,
              struct peer_chr **out_prev)
{
    struct peer_chr *prev;
    struct peer_chr *chr;

    prev = peer_chr_find_prev(svc, chr_val_handle);
    if (prev == NULL) {
        chr = SLIST_FIRST(&svc->chrs);
    } else {
        chr = SLIST_NEXT(prev, next);
    }

    if (chr != NULL && chr->chr.val_handle != chr_val_handle) {
        chr = NULL;
    }

    if (out_prev != NULL) {
        *out_prev = prev;
    }
    return chr;
}