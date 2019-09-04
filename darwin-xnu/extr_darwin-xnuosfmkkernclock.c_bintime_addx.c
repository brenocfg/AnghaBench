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
typedef  scalar_t__ uint64_t ;
struct bintime {scalar_t__ frac; int /*<<< orphan*/  sec; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
bintime_addx(struct bintime *_bt, uint64_t _x)
{
	uint64_t _u;

	_u = _bt->frac;
	_bt->frac += _x;
	if (_u > _bt->frac)
		_bt->sec++;
}