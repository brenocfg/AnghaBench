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
typedef  int /*<<< orphan*/  u8 ;
struct efx_filter_spec {int type; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  EFX_FILTER_TCP_WILD 129 
#define  EFX_FILTER_UDP_WILD 128 
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  __efx_filter_get_ipv4 (struct efx_filter_spec const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int efx_filter_get_ipv4_local(const struct efx_filter_spec *spec,
			      u8 *proto, __be32 *host, __be16 *port)
{
	__be32 host1;
	__be16 port1;

	switch (spec->type) {
	case EFX_FILTER_TCP_WILD:
		*proto = IPPROTO_TCP;
		__efx_filter_get_ipv4(spec, &host1, &port1, host, port);
		return 0;
	case EFX_FILTER_UDP_WILD:
		*proto = IPPROTO_UDP;
		__efx_filter_get_ipv4(spec, &host1, port, host, &port1);
		return 0;
	default:
		return -EINVAL;
	}
}