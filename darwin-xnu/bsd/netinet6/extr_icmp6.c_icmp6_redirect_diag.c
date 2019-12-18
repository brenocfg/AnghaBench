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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char* ip6_sprintf (struct in6_addr*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 

__attribute__((used)) static const char *
icmp6_redirect_diag(struct in6_addr *src6,
		    struct in6_addr *dst6,
		    struct in6_addr *tgt6)
{
	static char buf[1024];
	snprintf(buf, sizeof(buf), "(src=%s dst=%s tgt=%s)",
		ip6_sprintf(src6), ip6_sprintf(dst6), ip6_sprintf(tgt6));
	return buf;
}