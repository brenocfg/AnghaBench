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
 int /*<<< orphan*/  mipid_spi_driver ; 
 int /*<<< orphan*/  spi_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mipid_drv_cleanup(void)
{
	spi_unregister_driver(&mipid_spi_driver);
}