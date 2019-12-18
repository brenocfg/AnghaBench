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
struct in6_addr {int dummy; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int COOKIEBITS ; 
 int COOKIEMASK ; 
 int cookie_hash (struct in6_addr*,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static __u32 check_tcp_syn_cookie(__u32 cookie, struct in6_addr *saddr,
				  struct in6_addr *daddr, __be16 sport,
				  __be16 dport, __u32 sseq, __u32 count,
				  __u32 maxdiff)
{
	__u32 diff;

	cookie -= cookie_hash(saddr, daddr, sport, dport, 0, 0) + sseq;

	diff = (count - (cookie >> COOKIEBITS)) & ((__u32) -1 >> COOKIEBITS);
	if (diff >= maxdiff)
		return (__u32)-1;

	return (cookie -
		cookie_hash(saddr, daddr, sport, dport, count - diff, 1))
		& COOKIEMASK;
}