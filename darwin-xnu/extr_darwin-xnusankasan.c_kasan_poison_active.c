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
typedef  int uint8_t ;

/* Variables and functions */
#define  ASAN_GLOBAL_RZ 132 
#define  ASAN_HEAP_FREED 131 
#define  ASAN_HEAP_LEFT_RZ 130 
#define  ASAN_HEAP_RIGHT_RZ 129 
#define  ASAN_HEAP_RZ 128 
 int /*<<< orphan*/  TYPE_POISON_GLOBAL ; 
 int /*<<< orphan*/  TYPE_POISON_HEAP ; 
 int kasan_check_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
kasan_poison_active(uint8_t flags)
{
	switch (flags) {
	case ASAN_GLOBAL_RZ:
		return kasan_check_enabled(TYPE_POISON_GLOBAL);
	case ASAN_HEAP_RZ:
	case ASAN_HEAP_LEFT_RZ:
	case ASAN_HEAP_RIGHT_RZ:
	case ASAN_HEAP_FREED:
		return kasan_check_enabled(TYPE_POISON_HEAP);
	default:
		return true;
	};
}