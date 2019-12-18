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
 int XFRM6_TUNNEL_SPI_BYADDR_HSIZE ; 
 int XFRM6_TUNNEL_SPI_BYSPI_HSIZE ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfrm6_tunnel_spi_byaddr ; 
 int /*<<< orphan*/ * xfrm6_tunnel_spi_byspi ; 
 int /*<<< orphan*/ * xfrm6_tunnel_spi_kmem ; 

__attribute__((used)) static void xfrm6_tunnel_spi_fini(void)
{
	int i;

	for (i = 0; i < XFRM6_TUNNEL_SPI_BYADDR_HSIZE; i++) {
		if (!hlist_empty(&xfrm6_tunnel_spi_byaddr[i]))
			return;
	}
	for (i = 0; i < XFRM6_TUNNEL_SPI_BYSPI_HSIZE; i++) {
		if (!hlist_empty(&xfrm6_tunnel_spi_byspi[i]))
			return;
	}
	kmem_cache_destroy(xfrm6_tunnel_spi_kmem);
	xfrm6_tunnel_spi_kmem = NULL;
}