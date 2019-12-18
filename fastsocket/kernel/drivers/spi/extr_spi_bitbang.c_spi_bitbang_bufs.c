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
struct spi_transfer {int dummy; } ;
struct spi_device {struct spi_bitbang_cs* controller_state; } ;
struct spi_bitbang_cs {unsigned int nsecs; int (* txrx_bufs ) (struct spi_device*,int /*<<< orphan*/ ,unsigned int,struct spi_transfer*) ;int /*<<< orphan*/  txrx_word; } ;

/* Variables and functions */
 int stub1 (struct spi_device*,int /*<<< orphan*/ ,unsigned int,struct spi_transfer*) ; 

__attribute__((used)) static int spi_bitbang_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct spi_bitbang_cs	*cs = spi->controller_state;
	unsigned		nsecs = cs->nsecs;

	return cs->txrx_bufs(spi, cs->txrx_word, nsecs, t);
}