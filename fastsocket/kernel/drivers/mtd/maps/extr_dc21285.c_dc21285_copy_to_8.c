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
typedef  int /*<<< orphan*/  uint8_t ;
struct map_info {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 int /*<<< orphan*/  dc21285_write8 (struct map_info*,TYPE_1__,unsigned long) ; 

__attribute__((used)) static void dc21285_copy_to_8(struct map_info *map, unsigned long to, const void *from, ssize_t len)
{
	map_word d;
	d.x[0] = *((uint8_t*)from);
	dc21285_write8(map, d, to);
	from++;
	to++;
	len--;
}