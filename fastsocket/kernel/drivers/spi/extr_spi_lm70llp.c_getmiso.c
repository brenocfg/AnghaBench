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
struct spi_lm70llp {int /*<<< orphan*/  port; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int SIO ; 
 int parport_read_status (int /*<<< orphan*/ ) ; 
 struct spi_lm70llp* spidev_to_pp (struct spi_device*) ; 

__attribute__((used)) static inline int getmiso(struct spi_device *s)
{
	struct spi_lm70llp *pp = spidev_to_pp(s);
	return ((SIO == (parport_read_status(pp->port) & SIO)) ? 0 : 1 );
}