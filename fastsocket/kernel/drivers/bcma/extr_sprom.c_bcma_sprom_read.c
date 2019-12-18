#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;
struct bcma_bus {TYPE_1__ drv_cc; } ;

/* Variables and functions */
 int SSB_SPROMSIZE_WORDS_R4 ; 
 scalar_t__ bcma_read16 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bcma_sprom_read(struct bcma_bus *bus, u16 offset, u16 *sprom)
{
	int i;
	for (i = 0; i < SSB_SPROMSIZE_WORDS_R4; i++)
		sprom[i] = bcma_read16(bus->drv_cc.core,
				       offset + (i * 2));
}