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
#define  EFX_FILTER_TCP_FULL 129 
#define  EFX_FILTER_UDP_FULL 128 
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  __efx_filter_get_ipv4 (struct efx_filter_spec const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int efx_filter_get_ipv4_full(const struct efx_filter_spec *spec,
			     u8 *proto, __be32 *host, __be16 *port,
			     __be32 *rhost, __be16 *rport)
{
	switch (spec->type) {
	case EFX_FILTER_TCP_FULL:
		*proto = IPPROTO_TCP;
		break;
	case EFX_FILTER_UDP_FULL:
		*proto = IPPROTO_UDP;
		break;
	default:
		return -EINVAL;
	}

	__efx_filter_get_ipv4(spec, rhost, rport, host, port);
	return 0;
}