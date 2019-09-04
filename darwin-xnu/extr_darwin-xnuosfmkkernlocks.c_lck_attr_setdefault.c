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
struct TYPE_3__ {int /*<<< orphan*/  lck_attr_val; } ;
typedef  TYPE_1__ lck_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_DEBUG ; 
 int /*<<< orphan*/  LCK_ATTR_NONE ; 
 int LcksOpts ; 
 int enaLkDeb ; 

void
lck_attr_setdefault(
	lck_attr_t	*attr)
{
#if __arm__ || __arm64__
	/* <rdar://problem/4404579>: Using LCK_ATTR_DEBUG here causes panic at boot time for arm */
	attr->lck_attr_val =  LCK_ATTR_NONE;
#elif __i386__ || __x86_64__
#if     !DEBUG
 	if (LcksOpts & enaLkDeb)
 		attr->lck_attr_val =  LCK_ATTR_DEBUG;
 	else
 		attr->lck_attr_val =  LCK_ATTR_NONE;
#else
 	attr->lck_attr_val =  LCK_ATTR_DEBUG;
#endif	/* !DEBUG */
#else
#error Unknown architecture.
#endif	/* __arm__ */
}