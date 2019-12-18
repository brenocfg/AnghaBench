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
struct TYPE_2__ {scalar_t__ start_handle; } ;
struct peer_svc {TYPE_1__ svc; } ;
struct peer {int /*<<< orphan*/  svcs; } ;

/* Variables and functions */
 struct peer_svc* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct peer_svc* SLIST_NEXT (struct peer_svc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 struct peer_svc* peer_svc_find_prev (struct peer*,scalar_t__) ; 

__attribute__((used)) static struct peer_svc *
peer_svc_find(struct peer *peer, uint16_t svc_start_handle,
              struct peer_svc **out_prev)
{
    struct peer_svc *prev;
    struct peer_svc *svc;

    prev = peer_svc_find_prev(peer, svc_start_handle);
    if (prev == NULL) {
        svc = SLIST_FIRST(&peer->svcs);
    } else {
        svc = SLIST_NEXT(prev, next);
    }

    if (svc != NULL && svc->svc.start_handle != svc_start_handle) {
        svc = NULL;
    }

    if (out_prev != NULL) {
        *out_prev = prev;
    }
    return svc;
}