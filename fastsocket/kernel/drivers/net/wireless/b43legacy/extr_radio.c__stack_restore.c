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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
 size_t B43legacy_INTERFSTACK_SIZE ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 

__attribute__((used)) static u16 _stack_restore(u32 *stackptr,
			  u8 id, u16 offset)
{
	size_t i;

	B43legacy_WARN_ON(!((offset & 0xE000) == 0x0000));
	B43legacy_WARN_ON(!((id & 0xF8) == 0x00));
	for (i = 0; i < B43legacy_INTERFSTACK_SIZE; i++, stackptr++) {
		if ((*stackptr & 0x00001FFF) != offset)
			continue;
		if (((*stackptr & 0x00007000) >> 13) != id)
			continue;
		return ((*stackptr & 0xFFFF0000) >> 16);
	}
	B43legacy_BUG_ON(1);

	return 0;
}