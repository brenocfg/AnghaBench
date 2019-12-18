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

/* Variables and functions */
#define  MADV_DODUMP 141 
#define  MADV_DOFORK 140 
#define  MADV_DONTDUMP 139 
#define  MADV_DONTFORK 138 
#define  MADV_DONTNEED 137 
#define  MADV_HUGEPAGE 136 
#define  MADV_MERGEABLE 135 
#define  MADV_NOHUGEPAGE 134 
#define  MADV_NORMAL 133 
#define  MADV_RANDOM 132 
#define  MADV_REMOVE 131 
#define  MADV_SEQUENTIAL 130 
#define  MADV_UNMERGEABLE 129 
#define  MADV_WILLNEED 128 

__attribute__((used)) static int
madvise_behavior_valid(int behavior)
{
	switch (behavior) {
	case MADV_DOFORK:
	case MADV_DONTFORK:
	case MADV_NORMAL:
	case MADV_SEQUENTIAL:
	case MADV_RANDOM:
	case MADV_REMOVE:
	case MADV_WILLNEED:
	case MADV_DONTNEED:
#ifdef CONFIG_KSM
	case MADV_MERGEABLE:
	case MADV_UNMERGEABLE:
#endif
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	case MADV_HUGEPAGE:
	case MADV_NOHUGEPAGE:
#endif

	case MADV_DONTDUMP:
	case MADV_DODUMP:
		return 1;

	default:
		return 0;
	}
}