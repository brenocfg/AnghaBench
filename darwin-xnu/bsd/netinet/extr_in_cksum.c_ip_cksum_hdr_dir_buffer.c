#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ip {int dummy; } ;
struct TYPE_2__ {int ips_snd_swcsum_bytes; int ips_rcv_swcsum_bytes; int /*<<< orphan*/  ips_rcv_swcsum; int /*<<< orphan*/  ips_snd_swcsum; } ;

/* Variables and functions */
 scalar_t__ IP_HDR_ALIGNED_P (struct ip const*) ; 
 int /*<<< orphan*/  in_cksum_hdr (struct ip const*) ; 
 int /*<<< orphan*/  inet_cksum_buffer (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ ipstat ; 

uint16_t
ip_cksum_hdr_dir_buffer(const void *buffer, uint32_t hlen, uint32_t len,
    int out)
{
	const struct ip *ip = buffer;

	if (out) {
		ipstat.ips_snd_swcsum++;
		ipstat.ips_snd_swcsum_bytes += hlen;
	} else {
		ipstat.ips_rcv_swcsum++;
		ipstat.ips_rcv_swcsum_bytes += hlen;
	}

	if (hlen == sizeof (*ip) &&
	    len >= sizeof (*ip) && IP_HDR_ALIGNED_P(ip))
		return (in_cksum_hdr(ip));

	return (inet_cksum_buffer(buffer, 0, 0, hlen));
}