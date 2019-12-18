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
struct nouveau_event {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_mask (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
nv10_gpio_intr_disable(struct nouveau_event *event, int line)
{
	nv_wr32(event->priv, 0x001104, 0x00010001 << line);
	nv_mask(event->priv, 0x001144, 0x00010001 << line, 0x00000000);
}