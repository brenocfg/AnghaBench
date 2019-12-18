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
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int MDIO_CLK ; 
 int MDIO_WRITE1 ; 
 int /*<<< orphan*/  mdio_delay () ; 
 int /*<<< orphan*/  writeb (int,void*) ; 

__attribute__((used)) static void mdio_sync (void *mdio_addr)
{
	int i;

	DPRINTK ("ENTER\n");

	for (i = 32; i >= 0; i--) {
		writeb (MDIO_WRITE1, mdio_addr);
		mdio_delay ();
		writeb (MDIO_WRITE1 | MDIO_CLK, mdio_addr);
		mdio_delay ();
	}

	DPRINTK ("EXIT\n");
}