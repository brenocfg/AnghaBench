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
typedef  int /*<<< orphan*/  u8_t ;
struct mem {int used; scalar_t__ next; } ;
typedef  scalar_t__ mem_size_t ;
typedef  int mem_ptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 int LWIP_DBG_LEVEL_SERIOUS ; 
 int LWIP_DBG_LEVEL_SEVERE ; 
 int LWIP_DBG_TRACE ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int /*<<< orphan*/  LWIP_MEM_FREE_DECL_PROTECT () ; 
 int /*<<< orphan*/  LWIP_MEM_FREE_PROTECT () ; 
 int /*<<< orphan*/  LWIP_MEM_FREE_UNPROTECT () ; 
 int MEM_ALIGNMENT ; 
 int MEM_DEBUG ; 
 int /*<<< orphan*/  MEM_STATS_DEC_USED (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MEM_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SIZEOF_STRUCT_MEM ; 
 int /*<<< orphan*/  SYS_ARCH_DECL_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_UNPROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  illegal ; 
 int /*<<< orphan*/  lev ; 
 struct mem* lfree ; 
 int mem_free_count ; 
 int /*<<< orphan*/  plug_holes (struct mem*) ; 
 int /*<<< orphan*/ * ram ; 
 scalar_t__ ram_end ; 
 int /*<<< orphan*/  used ; 

void
mem_free(void *rmem)
{
  struct mem *mem;
  LWIP_MEM_FREE_DECL_PROTECT();

  if (rmem == NULL) {
    LWIP_DEBUGF(MEM_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_SERIOUS, ("mem_free(p == NULL) was called.\n"));
    return;
  }
  LWIP_ASSERT("mem_free: sanity check alignment", (((mem_ptr_t)rmem) & (MEM_ALIGNMENT-1)) == 0);

  LWIP_ASSERT("mem_free: legal memory", (u8_t *)rmem >= (u8_t *)ram &&
    (u8_t *)rmem < (u8_t *)ram_end);

  if ((u8_t *)rmem < (u8_t *)ram || (u8_t *)rmem >= (u8_t *)ram_end) {
    SYS_ARCH_DECL_PROTECT(lev);
    LWIP_DEBUGF(MEM_DEBUG | LWIP_DBG_LEVEL_SEVERE, ("mem_free: illegal memory\n"));
    /* protect mem stats from concurrent access */
    SYS_ARCH_PROTECT(lev);
    MEM_STATS_INC(illegal);
    SYS_ARCH_UNPROTECT(lev);
    return;
  }
  /* protect the heap from concurrent access */
  LWIP_MEM_FREE_PROTECT();
  /* Get the corresponding struct mem ... */
  mem = (struct mem *)(void *)((u8_t *)rmem - SIZEOF_STRUCT_MEM);
  /* ... which has to be in a used state ... */
  LWIP_ASSERT("mem_free: mem->used", mem->used);
  /* ... and is now unused. */
  mem->used = 0;

  if (mem < lfree) {
    /* the newly freed struct is now the lowest */
    lfree = mem;
  }

  MEM_STATS_DEC_USED(used, mem->next - (mem_size_t)(((u8_t *)mem - ram)));

  /* finally, see if prev or next are free also */
  plug_holes(mem);
#if LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT
  mem_free_count = 1;
#endif /* LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT */
  LWIP_MEM_FREE_UNPROTECT();
}