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
 int /*<<< orphan*/  spi_register_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipid_drv_init(void)
{
	spi_register_driver(&mipid_spi_driver);

	return 0;
}