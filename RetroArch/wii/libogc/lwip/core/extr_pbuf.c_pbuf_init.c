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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct pbuf {int len; int tot_len; struct pbuf* next; int /*<<< orphan*/  flags; scalar_t__ payload; } ;
struct TYPE_3__ {scalar_t__ avail; } ;
struct TYPE_4__ {TYPE_1__ pbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_SemInit (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ MEM_ALIGN (void*) ; 
 int /*<<< orphan*/  PBUF_FLAG_POOL ; 
 int PBUF_POOL_BUFSIZE ; 
 scalar_t__ PBUF_POOL_SIZE ; 
 TYPE_2__ lwip_stats ; 
 struct pbuf* pbuf_pool ; 
 scalar_t__ pbuf_pool_alloc_lock ; 
 scalar_t__ pbuf_pool_free_lock ; 
 int /*<<< orphan*/  pbuf_pool_free_sem ; 
 void* pbuf_pool_memory ; 

void
pbuf_init(void)
{
  struct pbuf *p, *q = NULL;
  u16_t i;

  pbuf_pool = (struct pbuf *)MEM_ALIGN(pbuf_pool_memory);

#if PBUF_STATS
  lwip_stats.pbuf.avail = PBUF_POOL_SIZE;
#endif /* PBUF_STATS */

  /* Set up ->next pointers to link the pbufs of the pool together */
  p = pbuf_pool;

  for(i = 0; i < PBUF_POOL_SIZE; ++i) {
    p->next = (struct pbuf *)((u8_t *)p + PBUF_POOL_BUFSIZE + sizeof(struct pbuf));
    p->len = p->tot_len = PBUF_POOL_BUFSIZE;
    p->payload = MEM_ALIGN((void *)((u8_t *)p + sizeof(struct pbuf)));
    p->flags = PBUF_FLAG_POOL;
    q = p;
    p = p->next;
  }

  /* The ->next pointer of last pbuf is NULL to indicate that there
     are no more pbufs in the pool */
  q->next = NULL;

#if !SYS_LIGHTWEIGHT_PROT
  pbuf_pool_alloc_lock = 0;
  pbuf_pool_free_lock = 0;
  LWP_SemInit(&pbuf_pool_free_sem,1,1);
#endif
}