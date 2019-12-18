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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_DMA (unsigned char) ; 
 int /*<<< orphan*/  ADB_SRCIN (unsigned char) ; 
 int /*<<< orphan*/  vortex_route (int /*<<< orphan*/ *,int,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_connection_adbdma_src(vortex_t * vortex, int en, unsigned char ch,
			     unsigned char adbdma, unsigned char src)
{
	vortex_route(vortex, en, ch, ADB_DMA(adbdma), ADB_SRCIN(src));
}