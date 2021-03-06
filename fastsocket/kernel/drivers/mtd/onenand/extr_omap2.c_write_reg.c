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
struct TYPE_2__ {scalar_t__ base; } ;
struct omap2_onenand {TYPE_1__ onenand; } ;

/* Variables and functions */
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline void write_reg(struct omap2_onenand *c, unsigned short value,
			     int reg)
{
	writew(value, c->onenand.base + reg);
}