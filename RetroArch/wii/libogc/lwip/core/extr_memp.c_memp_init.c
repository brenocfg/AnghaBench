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
typedef  size_t u16_t ;
struct memp {struct memp* next; } ;
struct TYPE_4__ {TYPE_1__* memp; } ;
struct TYPE_3__ {scalar_t__ avail; scalar_t__ err; scalar_t__ max; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_SemInit (int /*<<< orphan*/ *,int,int) ; 
 size_t MEMP_MAX ; 
 scalar_t__ MEM_ALIGN (int /*<<< orphan*/ *) ; 
 size_t MEM_ALIGN_SIZE (scalar_t__) ; 
 TYPE_2__ lwip_stats ; 
 int /*<<< orphan*/ * memp_memory ; 
 scalar_t__* memp_num ; 
 scalar_t__* memp_sizes ; 
 struct memp** memp_tab ; 
 int /*<<< orphan*/  mutex ; 

void
memp_init(void)
{
  struct memp *m, *memp;
  u16_t i, j;
  u16_t size;

#if MEMP_STATS
  for(i = 0; i < MEMP_MAX; ++i) {
    lwip_stats.memp[i].used = lwip_stats.memp[i].max =
      lwip_stats.memp[i].err = 0;
    lwip_stats.memp[i].avail = memp_num[i];
  }
#endif /* MEMP_STATS */

  memp = (struct memp *)&memp_memory[0];
  for(i = 0; i < MEMP_MAX; ++i) {
    size = MEM_ALIGN_SIZE(memp_sizes[i] + sizeof(struct memp));
    if (memp_num[i] > 0) {
      memp_tab[i] = memp;
      m = memp;

      for(j = 0; j < memp_num[i]; ++j) {
  m->next = (struct memp *)MEM_ALIGN((u8_t *)m + size);
  memp = m;
  m = m->next;
      }
      memp->next = NULL;
      memp = m;
    } else {
      memp_tab[i] = NULL;
    }
  }

#if !SYS_LIGHTWEIGHT_PROT
  LWP_SemInit(&mutex,1,1);
#endif

}