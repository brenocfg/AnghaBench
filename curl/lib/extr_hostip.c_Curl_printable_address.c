#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct TYPE_3__ {int ai_family; scalar_t__ ai_addr; } ;
typedef  TYPE_1__ Curl_addrinfo ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 char const* Curl_inet_ntop (int,void const*,char*,size_t) ; 

const char *
Curl_printable_address(const Curl_addrinfo *ai, char *buf, size_t bufsize)
{
  const struct sockaddr_in *sa4;
  const struct in_addr *ipaddr4;
#ifdef ENABLE_IPV6
  const struct sockaddr_in6 *sa6;
  const struct in6_addr *ipaddr6;
#endif

  switch(ai->ai_family) {
    case AF_INET:
      sa4 = (const void *)ai->ai_addr;
      ipaddr4 = &sa4->sin_addr;
      return Curl_inet_ntop(ai->ai_family, (const void *)ipaddr4, buf,
                            bufsize);
#ifdef ENABLE_IPV6
    case AF_INET6:
      sa6 = (const void *)ai->ai_addr;
      ipaddr6 = &sa6->sin6_addr;
      return Curl_inet_ntop(ai->ai_family, (const void *)ipaddr6, buf,
                            bufsize);
#endif
    default:
      break;
  }
  return NULL;
}