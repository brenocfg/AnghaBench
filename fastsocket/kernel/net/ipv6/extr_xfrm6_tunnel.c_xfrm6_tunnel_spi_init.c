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
struct xfrm6_tunnel_spi {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int XFRM6_TUNNEL_SPI_BYADDR_HSIZE ; 
 int XFRM6_TUNNEL_SPI_BYSPI_HSIZE ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xfrm6_tunnel_spi ; 
 int /*<<< orphan*/ * xfrm6_tunnel_spi_byaddr ; 
 int /*<<< orphan*/ * xfrm6_tunnel_spi_byspi ; 
 int /*<<< orphan*/  xfrm6_tunnel_spi_kmem ; 

__attribute__((used)) static int xfrm6_tunnel_spi_init(void)
{
	int i;

	xfrm6_tunnel_spi = 0;
	xfrm6_tunnel_spi_kmem = kmem_cache_create("xfrm6_tunnel_spi",
						  sizeof(struct xfrm6_tunnel_spi),
						  0, SLAB_HWCACHE_ALIGN,
						  NULL);
	if (!xfrm6_tunnel_spi_kmem)
		return -ENOMEM;

	for (i = 0; i < XFRM6_TUNNEL_SPI_BYADDR_HSIZE; i++)
		INIT_HLIST_HEAD(&xfrm6_tunnel_spi_byaddr[i]);
	for (i = 0; i < XFRM6_TUNNEL_SPI_BYSPI_HSIZE; i++)
		INIT_HLIST_HEAD(&xfrm6_tunnel_spi_byspi[i]);
	return 0;
}