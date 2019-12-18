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
struct mem {scalar_t__ used; size_t next; int prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 size_t MEM_SIZE ; 
 struct mem* lfree ; 
 int /*<<< orphan*/ * ram ; 
 scalar_t__ ram_end ; 

__attribute__((used)) static void
plug_holes(struct mem *mem)
{
  struct mem *nmem;
  struct mem *pmem;

  LWIP_ASSERT("plug_holes: mem >= ram", (u8_t *)mem >= ram);
  LWIP_ASSERT("plug_holes: mem < ram_end", (u8_t *)mem < (u8_t *)ram_end);
  LWIP_ASSERT("plug_holes: mem->used == 0", mem->used == 0);

  /* plug hole forward */
  LWIP_ASSERT("plug_holes: mem->next <= MEM_SIZE", mem->next <= MEM_SIZE);

  nmem = (struct mem *)&ram[mem->next];
  if (mem != nmem && nmem->used == 0 && (u8_t *)nmem != (u8_t *)ram_end) {
    if (lfree == nmem) {
      lfree = mem;
    }
    mem->next = nmem->next;
    ((struct mem *)&ram[nmem->next])->prev = (u8_t *)mem - ram;
  }

  /* plug hole backward */
  pmem = (struct mem *)&ram[mem->prev];
  if (pmem != mem && pmem->used == 0) {
    if (lfree == mem) {
      lfree = pmem;
    }
    pmem->next = mem->next;
    ((struct mem *)&ram[mem->next])->prev = (u8_t *)pmem - ram;
  }

}