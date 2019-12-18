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

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  errno ; 
 char* inet_ntop4 (unsigned char const*,char*,size_t) ; 
 char* inet_ntop6 (unsigned char const*,char*,size_t) ; 

char *Curl_inet_ntop(int af, const void *src, char *buf, size_t size)
{
  switch(af) {
  case AF_INET:
    return inet_ntop4((const unsigned char *)src, buf, size);
#ifdef ENABLE_IPV6
  case AF_INET6:
    return inet_ntop6((const unsigned char *)src, buf, size);
#endif
  default:
    errno = EAFNOSUPPORT;
    return NULL;
  }
}