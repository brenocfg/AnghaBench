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

/* Variables and functions */
 int /*<<< orphan*/  memb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uip_pool_pbufs ; 
 int /*<<< orphan*/  uip_rom_pbufs ; 

void uip_pbuf_init()
{
	memb_init(&uip_pool_pbufs);
	memb_init(&uip_rom_pbufs);
}