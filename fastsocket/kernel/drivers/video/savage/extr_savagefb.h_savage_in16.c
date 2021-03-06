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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ vbase; } ;
struct savagefb_par {TYPE_1__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static inline u16 savage_in16(u32 addr, struct savagefb_par *par)
{
	return readw(par->mmio.vbase + addr);
}