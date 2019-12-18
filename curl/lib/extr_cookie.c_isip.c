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

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ Curl_inet_pton (int /*<<< orphan*/ ,char const*,struct in_addr*) ; 
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool isip(const char *domain)
{
  struct in_addr addr;
#ifdef ENABLE_IPV6
  struct in6_addr addr6;
#endif

  if(Curl_inet_pton(AF_INET, domain, &addr)
#ifdef ENABLE_IPV6
     || Curl_inet_pton(AF_INET6, domain, &addr6)
#endif
    ) {
    /* domain name given as IP address */
    return TRUE;
  }

  return FALSE;
}