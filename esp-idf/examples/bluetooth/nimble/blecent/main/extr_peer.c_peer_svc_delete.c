#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct peer_svc {int /*<<< orphan*/  chrs; } ;
struct peer_chr {int dummy; } ;

/* Variables and functions */
 struct peer_chr* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  os_memblock_put (int /*<<< orphan*/ *,struct peer_svc*) ; 
 int /*<<< orphan*/  peer_chr_delete (struct peer_chr*) ; 
 int /*<<< orphan*/  peer_svc_pool ; 

__attribute__((used)) static void
peer_svc_delete(struct peer_svc *svc)
{
    struct peer_chr *chr;

    while ((chr = SLIST_FIRST(&svc->chrs)) != NULL) {
        SLIST_REMOVE_HEAD(&svc->chrs, next);
        peer_chr_delete(chr);
    }

    os_memblock_put(&peer_svc_pool, svc);
}