#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int FIFO_MASK ; 
 int /*<<< orphan*/  FIFO_SIZE ; 
 int FIFO_U1 ; 
 scalar_t__ VORTEX_FIFO_WTCTRL ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vortex_fifo_clearwtdata (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_fifo_wtinitialize(vortex_t * vortex, int fifo, int j)
{
	vortex_fifo_clearwtdata(vortex, fifo, FIFO_SIZE);
#ifdef CHIP_AU8820
	hwwrite(vortex->mmio, VORTEX_FIFO_WTCTRL + (fifo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xb)));
#else
	hwwrite(vortex->mmio, VORTEX_FIFO_WTCTRL + (fifo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xc)));
#endif
}