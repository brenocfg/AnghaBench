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
typedef  int u8 ;
struct efx_filter_spec {int flags; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 int EFX_FILTER_FLAG_RX ; 
 scalar_t__ EFX_FILTER_TCP_FULL ; 
 scalar_t__ EFX_FILTER_UDP_FULL ; 
 scalar_t__ EFX_FILTER_UNSPEC ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  __efx_filter_set_ipv4 (struct efx_filter_spec*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

int efx_filter_set_ipv4_full(struct efx_filter_spec *spec, u8 proto,
			     __be32 host, __be16 port,
			     __be32 rhost, __be16 rport)
{
	EFX_BUG_ON_PARANOID(!(spec->flags & EFX_FILTER_FLAG_RX));

	/* This cannot currently be combined with other filtering */
	if (spec->type != EFX_FILTER_UNSPEC)
		return -EPROTONOSUPPORT;

	if (port == 0 || rport == 0)
		return -EINVAL;

	switch (proto) {
	case IPPROTO_TCP:
		spec->type = EFX_FILTER_TCP_FULL;
		break;
	case IPPROTO_UDP:
		spec->type = EFX_FILTER_UDP_FULL;
		break;
	default:
		return -EPROTONOSUPPORT;
	}

	__efx_filter_set_ipv4(spec, rhost, rport, host, port);
	return 0;
}