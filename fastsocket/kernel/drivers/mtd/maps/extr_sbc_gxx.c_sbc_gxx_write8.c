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
struct map_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 unsigned long WINDOW_MASK ; 
 scalar_t__ iomapadr ; 
 int /*<<< orphan*/  sbc_gxx_page (struct map_info*,unsigned long) ; 
 int /*<<< orphan*/  sbc_gxx_spin ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sbc_gxx_write8(struct map_info *map, map_word d, unsigned long adr)
{
	spin_lock(&sbc_gxx_spin);
	sbc_gxx_page(map, adr);
	writeb(d.x[0], iomapadr + (adr & WINDOW_MASK));
	spin_unlock(&sbc_gxx_spin);
}