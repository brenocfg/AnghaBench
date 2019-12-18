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
struct mem {int used; int next; } ;
struct TYPE_3__ {int /*<<< orphan*/  used; int /*<<< orphan*/  err; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;

/* Variables and functions */
 int DBG_TRACE ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int /*<<< orphan*/  LWP_SemPost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_SemWait (int /*<<< orphan*/ ) ; 
 int MEM_DEBUG ; 
 int /*<<< orphan*/ * SIZEOF_STRUCT_MEM ; 
 struct mem* lfree ; 
 TYPE_2__ lwip_stats ; 
 int /*<<< orphan*/  mem_sem ; 
 int /*<<< orphan*/  plug_holes (struct mem*) ; 
 int /*<<< orphan*/ * ram ; 
 scalar_t__ ram_end ; 

void
mem_free(void *rmem)
{
  struct mem *mem;

  if (rmem == NULL) {
    LWIP_DEBUGF(MEM_DEBUG | DBG_TRACE | 2, ("mem_free(p == NULL) was called.\n"));
    return;
  }

  LWP_SemWait(mem_sem);

  LWIP_ASSERT("mem_free: legal memory", (u8_t *)rmem >= (u8_t *)ram &&
    (u8_t *)rmem < (u8_t *)ram_end);

  if ((u8_t *)rmem < (u8_t *)ram || (u8_t *)rmem >= (u8_t *)ram_end) {
    LWIP_DEBUGF(MEM_DEBUG | 3, ("mem_free: illegal memory\n"));
#if MEM_STATS
    ++lwip_stats.mem.err;
#endif /* MEM_STATS */
    LWP_SemPost(mem_sem);
    return;
  }
  mem = (struct mem *)((u8_t *)rmem - SIZEOF_STRUCT_MEM);

  LWIP_ASSERT("mem_free: mem->used", mem->used);

  mem->used = 0;

  if (mem < lfree) {
    lfree = mem;
  }

#if MEM_STATS
  lwip_stats.mem.used -= mem->next - ((u8_t *)mem - ram);

#endif /* MEM_STATS */
  plug_holes(mem);
  LWP_SemPost(mem_sem);
}