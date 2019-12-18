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
struct memp {struct memp* next; } ;
typedef  size_t memp_t ;
struct TYPE_4__ {TYPE_1__* memp; } ;
struct TYPE_3__ {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_SemPost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_SemWait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_DECL_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_PROTECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_ARCH_UNPROTECT (int /*<<< orphan*/ ) ; 
 TYPE_2__ lwip_stats ; 
 int /*<<< orphan*/  memp_sanity () ; 
 struct memp** memp_tab ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  old_level ; 

void
memp_free(memp_t type, void *mem)
{
  struct memp *memp;
#if SYS_LIGHTWEIGHT_PROT
  SYS_ARCH_DECL_PROTECT(old_level);
#endif /* SYS_LIGHTWEIGHT_PROT */

  if (mem == NULL) {
    return;
  }
  memp = (struct memp *)((u8_t *)mem - sizeof(struct memp));

#if SYS_LIGHTWEIGHT_PROT
    SYS_ARCH_PROTECT(old_level);
#else /* SYS_LIGHTWEIGHT_PROT */
  LWP_SemWait(mutex);
#endif /* SYS_LIGHTWEIGHT_PROT */

#if MEMP_STATS
  lwip_stats.memp[type].used--;
#endif /* MEMP_STATS */

  memp->next = memp_tab[type];
  memp_tab[type] = memp;

#if MEMP_SANITY_CHECK
  LWIP_ASSERT("memp sanity", memp_sanity());
#endif

#if SYS_LIGHTWEIGHT_PROT
  SYS_ARCH_UNPROTECT(old_level);
#else /* SYS_LIGHTWEIGHT_PROT */
    LWP_SemPost(mutex);
#endif /* SYS_LIGHTWEIGHT_PROT */
}