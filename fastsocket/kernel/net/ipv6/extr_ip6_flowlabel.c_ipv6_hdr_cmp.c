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
struct ipv6_opt_hdr {int hdrlen; } ;

/* Variables and functions */
 int memcmp (struct ipv6_opt_hdr*,struct ipv6_opt_hdr*,int) ; 

__attribute__((used)) static int ipv6_hdr_cmp(struct ipv6_opt_hdr *h1, struct ipv6_opt_hdr *h2)
{
	if (h1 == h2)
		return 0;
	if (h1 == NULL || h2 == NULL)
		return 1;
	if (h1->hdrlen != h2->hdrlen)
		return 1;
	return memcmp(h1+1, h2+1, ((h1->hdrlen+1)<<3) - sizeof(*h1));
}