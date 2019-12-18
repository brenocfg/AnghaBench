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
 int /*<<< orphan*/  btmemb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_pbufs ; 
 int /*<<< orphan*/  rom_pbufs ; 

void btpbuf_init()
{
	btmemb_init(&pool_pbufs);
	btmemb_init(&rom_pbufs);
}