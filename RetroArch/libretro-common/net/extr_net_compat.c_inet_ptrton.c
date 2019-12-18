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

/* Variables and functions */
 int inet_aton (char const*,struct in_addr*) ; 
 int inet_pton (int,char const*,void*) ; 
 int sceNetInetPton (int,char const*,void*) ; 

int inet_ptrton(int af, const char *src, void *dst)
{
#if defined(VITA) || defined(__ORBIS__)
   return sceNetInetPton(af, src, dst);
#elif defined(GEKKO) || defined(_WIN32)
   /* TODO/FIXME - should use InetPton on Vista and later */
   return inet_aton(src, (struct in_addr*)dst);
#else
   return inet_pton(af, src, dst);
#endif
}