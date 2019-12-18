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
 int /*<<< orphan*/  b43_pcmcia_driver ; 
 int /*<<< orphan*/  pcmcia_unregister_driver (int /*<<< orphan*/ *) ; 

void b43_pcmcia_exit(void)
{
	pcmcia_unregister_driver(&b43_pcmcia_driver);
}