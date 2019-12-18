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
 int /*<<< orphan*/  fs_enet_bb_mdio_driver ; 
 int /*<<< orphan*/  of_unregister_platform_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fs_enet_mdio_bb_exit(void)
{
	of_unregister_platform_driver(&fs_enet_bb_mdio_driver);
}