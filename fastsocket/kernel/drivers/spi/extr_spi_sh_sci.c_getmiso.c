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
typedef  int u32 ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct sh_sci_spi {int dummy; } ;

/* Variables and functions */
 int PIN_RXD ; 
 int /*<<< orphan*/  SCSPTR (struct sh_sci_spi*) ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 struct sh_sci_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 getmiso(struct spi_device *dev)
{
	struct sh_sci_spi *sp = spi_master_get_devdata(dev->master);

	return (ioread8(SCSPTR(sp)) & PIN_RXD) ? 1 : 0;
}