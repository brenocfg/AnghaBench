#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fire; } ;
typedef  TYPE_1__ wd_cntrl ;
typedef  int u64 ;
typedef  int u32 ;
struct uulc {int ull; int* ul; } ;
typedef  int s64 ;

/* Variables and functions */
 int diff_ticks (int,int /*<<< orphan*/ ) ; 
 int gettime () ; 
 int /*<<< orphan*/  mtdec (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void __lwp_wd_settimer(wd_cntrl *wd)
{
	u64 now;
	s64 diff;
	union uulc {
		u64 ull;
		u32 ul[2];
	} v;

	now = gettime();
	v.ull = diff = diff_ticks(now,wd->fire);
#ifdef _LWPWD_DEBUG
	printf("__lwp_wd_settimer(%p,%llu,%lld)\n",wd,wd->fire,diff);
#endif
	if(diff<=0) {
#ifdef _LWPWD_DEBUG
		printf(" __lwp_wd_settimer(0): %lld<=0\n",diff);
#endif
		wd->fire = 0;
		mtdec(0);
	} else if(diff<0x0000000080000000LL) {
#ifdef _LWPWD_DEBUG
		printf("__lwp_wd_settimer(%d): %lld<0x0000000080000000LL\n",v.ul[1],diff);
#endif
		mtdec(v.ul[1]);
	} else {
#ifdef _LWPWD_DEBUG
		printf("__lwp_wd_settimer(0x7fffffff)\n");
#endif
		mtdec(0x7fffffff);
	}
}