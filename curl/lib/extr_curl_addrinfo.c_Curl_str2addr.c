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
struct in_addr {int dummy; } ;
typedef  struct in_addr in6_addr ;
typedef  int /*<<< orphan*/  Curl_addrinfo ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ Curl_inet_pton (int /*<<< orphan*/ ,char*,struct in_addr*) ; 
 int /*<<< orphan*/ * Curl_ip2addr (int /*<<< orphan*/ ,struct in_addr*,char*,int) ; 

Curl_addrinfo *Curl_str2addr(char *address, int port)
{
  struct in_addr in;
  if(Curl_inet_pton(AF_INET, address, &in) > 0)
    /* This is a dotted IP address 123.123.123.123-style */
    return Curl_ip2addr(AF_INET, &in, address, port);
#ifdef ENABLE_IPV6
  {
    struct in6_addr in6;
    if(Curl_inet_pton(AF_INET6, address, &in6) > 0)
      /* This is a dotted IPv6 address ::1-style */
      return Curl_ip2addr(AF_INET6, &in6, address, port);
  }
#endif
  return NULL; /* bad input format */
}