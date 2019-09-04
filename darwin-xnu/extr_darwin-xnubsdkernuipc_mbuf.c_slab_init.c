#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {unsigned int sl_len; int sl_refcnt; int sl_chunks; void* sl_head; void* sl_base; int /*<<< orphan*/  sl_flags; int /*<<< orphan*/  sl_class; } ;
typedef  TYPE_1__ mcl_slab_t ;
typedef  int /*<<< orphan*/  mbuf_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  slab_detach (TYPE_1__*) ; 

__attribute__((used)) static void
slab_init(mcl_slab_t *sp, mbuf_class_t class, u_int32_t flags,
    void *base, void *head, unsigned int len, int refcnt, int chunks)
{
	sp->sl_class = class;
	sp->sl_flags = flags;
	sp->sl_base = base;
	sp->sl_head = head;
	sp->sl_len = len;
	sp->sl_refcnt = refcnt;
	sp->sl_chunks = chunks;
	slab_detach(sp);
}