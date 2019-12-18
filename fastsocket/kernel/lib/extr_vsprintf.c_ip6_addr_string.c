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
struct printf_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_compressed_string (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ip6_string (char*,int /*<<< orphan*/  const*,char const*) ; 
 char* string (char*,char*,char*,struct printf_spec) ; 

__attribute__((used)) static char *ip6_addr_string(char *buf, char *end, const u8 *addr,
			     struct printf_spec spec, const char *fmt)
{
	char ip6_addr[sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255")];

	if (fmt[0] == 'I' && fmt[2] == 'c')
		ip6_compressed_string(ip6_addr, addr);
	else
		ip6_string(ip6_addr, addr, fmt);

	return string(buf, end, ip6_addr, spec);
}