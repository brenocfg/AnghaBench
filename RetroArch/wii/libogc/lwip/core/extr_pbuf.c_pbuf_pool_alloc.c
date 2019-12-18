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
struct pbuf {struct pbuf* next; } ;
struct TYPE_3__ {scalar_t__ used; scalar_t__ max; int /*<<< orphan*/  alloc_locked; } ;
struct TYPE_4__ {TYPE_1__ pbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_ARCH_DECL_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_UNPROTECT (int /*<<< orphan*/ ) ; 
 TYPE_2__ lwip_stats ; 
 int /*<<< orphan*/  old_level ; 
 struct pbuf* pbuf_pool ; 
 int pbuf_pool_alloc_lock ; 
 scalar_t__ pbuf_pool_free_lock ; 

__attribute__((used)) static struct pbuf *
pbuf_pool_alloc(void)
{
  struct pbuf *p = NULL;

  SYS_ARCH_DECL_PROTECT(old_level);
  SYS_ARCH_PROTECT(old_level);

#if !SYS_LIGHTWEIGHT_PROT
  /* Next, check the actual pbuf pool, but if the pool is locked, we
     pretend to be out of buffers and return NULL. */
  if (pbuf_pool_free_lock) {
#if PBUF_STATS
    ++lwip_stats.pbuf.alloc_locked;
#endif /* PBUF_STATS */
    return NULL;
  }
  pbuf_pool_alloc_lock = 1;
  if (!pbuf_pool_free_lock) {
#endif /* SYS_LIGHTWEIGHT_PROT */
    p = pbuf_pool;
    if (p) {
      pbuf_pool = p->next;
    }
#if !SYS_LIGHTWEIGHT_PROT
#if PBUF_STATS
  } else {
    ++lwip_stats.pbuf.alloc_locked;
#endif /* PBUF_STATS */
  }
  pbuf_pool_alloc_lock = 0;
#endif /* SYS_LIGHTWEIGHT_PROT */

#if PBUF_STATS
  if (p != NULL) {
    ++lwip_stats.pbuf.used;
    if (lwip_stats.pbuf.used > lwip_stats.pbuf.max) {
      lwip_stats.pbuf.max = lwip_stats.pbuf.used;
    }
  }
#endif /* PBUF_STATS */

  SYS_ARCH_UNPROTECT(old_level);
  return p;
}