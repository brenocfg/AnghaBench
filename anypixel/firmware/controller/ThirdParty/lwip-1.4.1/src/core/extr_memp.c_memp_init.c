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
typedef  size_t u16_t ;
struct memp {struct memp* next; } ;

/* Variables and functions */
 scalar_t__ LWIP_MEM_ALIGN (int /*<<< orphan*/ ) ; 
 size_t MEMP_MAX ; 
 int MEMP_SANITY_REGION_AFTER_ALIGNED ; 
 int MEMP_SIZE ; 
 int /*<<< orphan*/  MEMP_STATS_AVAIL (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  avail ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  max ; 
 scalar_t__* memp_bases ; 
 int /*<<< orphan*/  memp_memory ; 
 size_t* memp_num ; 
 int /*<<< orphan*/  memp_overflow_check_all () ; 
 int /*<<< orphan*/  memp_overflow_init () ; 
 int* memp_sizes ; 
 struct memp** memp_tab ; 
 int /*<<< orphan*/  used ; 

void
memp_init(void)
{
  struct memp *memp;
  u16_t i, j;

  for (i = 0; i < MEMP_MAX; ++i) {
    MEMP_STATS_AVAIL(used, i, 0);
    MEMP_STATS_AVAIL(max, i, 0);
    MEMP_STATS_AVAIL(err, i, 0);
    MEMP_STATS_AVAIL(avail, i, memp_num[i]);
  }

#if !MEMP_SEPARATE_POOLS
  memp = (struct memp *)LWIP_MEM_ALIGN(memp_memory);
#endif /* !MEMP_SEPARATE_POOLS */
  /* for every pool: */
  for (i = 0; i < MEMP_MAX; ++i) {
    memp_tab[i] = NULL;
#if MEMP_SEPARATE_POOLS
    memp = (struct memp*)memp_bases[i];
#endif /* MEMP_SEPARATE_POOLS */
    /* create a linked list of memp elements */
    for (j = 0; j < memp_num[i]; ++j) {
      memp->next = memp_tab[i];
      memp_tab[i] = memp;
      memp = (struct memp *)(void *)((u8_t *)memp + MEMP_SIZE + memp_sizes[i]
#if MEMP_OVERFLOW_CHECK
        + MEMP_SANITY_REGION_AFTER_ALIGNED
#endif
      );
    }
  }
#if MEMP_OVERFLOW_CHECK
  memp_overflow_init();
  /* check everything a first time to see if it worked */
  memp_overflow_check_all();
#endif /* MEMP_OVERFLOW_CHECK */
}