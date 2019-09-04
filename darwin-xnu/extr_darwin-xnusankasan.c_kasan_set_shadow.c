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
typedef  scalar_t__ uptr ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  __nosan_memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
kasan_set_shadow(uptr addr, size_t sz, uint8_t val)
{
	__nosan_memset((void *)addr, val, sz);
}