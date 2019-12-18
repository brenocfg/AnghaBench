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
 int /*<<< orphan*/  bt_mrvl_sdio ; 
 int /*<<< orphan*/  sdio_unregister_driver (int /*<<< orphan*/ *) ; 
 int user_rmmod ; 

__attribute__((used)) static void btmrvl_sdio_exit_module(void)
{
	/* Set the flag as user is removing this module. */
	user_rmmod = 1;

	sdio_unregister_driver(&bt_mrvl_sdio);
}