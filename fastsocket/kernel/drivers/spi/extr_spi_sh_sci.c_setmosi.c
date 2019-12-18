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
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_TXD ; 
 int /*<<< orphan*/  setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void setmosi(struct spi_device *dev, int on)
{
	setbits(spi_master_get_devdata(dev->master), PIN_TXD, on);
}