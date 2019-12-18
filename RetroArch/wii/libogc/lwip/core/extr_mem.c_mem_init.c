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
struct mem {size_t next; size_t prev; int used; } ;
struct TYPE_3__ {size_t avail; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_SemInit (int /*<<< orphan*/ *,int,int) ; 
 size_t MEM_SIZE ; 
 struct mem* lfree ; 
 TYPE_2__ lwip_stats ; 
 int /*<<< orphan*/  mem_sem ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ram ; 
 struct mem* ram_end ; 

void
mem_init(void)
{
  struct mem *mem;

  memset(ram, 0, MEM_SIZE);
  mem = (struct mem *)ram;
  mem->next = MEM_SIZE;
  mem->prev = 0;
  mem->used = 0;
  ram_end = (struct mem *)&ram[MEM_SIZE];
  ram_end->used = 1;
  ram_end->next = MEM_SIZE;
  ram_end->prev = MEM_SIZE;

  LWP_SemInit(&mem_sem,1,1);

  lfree = (struct mem *)ram;

#if MEM_STATS
  lwip_stats.mem.avail = MEM_SIZE;
#endif /* MEM_STATS */
}