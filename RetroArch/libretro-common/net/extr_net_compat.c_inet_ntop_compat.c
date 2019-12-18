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
struct sockaddr_in6 {int sin_family; int sin6_family; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr_in {int sin_family; int sin6_family; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct in_addr6_compat {int dummy; } ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* inet_ntop (int,void const*,char*,int /*<<< orphan*/ ) ; 
 char const* isockaddr_ntop (int,void const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 char const* sceNetInetNtop (int,void const*,char*,int /*<<< orphan*/ ) ; 

const char *inet_ntop_compat(int af, const void *src, char *dst, socklen_t cnt)
{
#if defined(VITA) || defined(__ORBIS__)
   return sceNetInetNtop(af,src,dst,cnt);
#elif defined(WIIU)
   return inet_ntop(af, src, dst, cnt);
#elif defined(_XBOX)
   return isockaddr_ntop(af, src, dst, cnt);
#elif defined(_WIN32)
   if (af == AF_INET)
   {
      struct sockaddr_in in;
      memset(&in, 0, sizeof(in));
      in.sin_family = AF_INET;
      memcpy(&in.sin_addr, src, sizeof(struct in_addr));
      getnameinfo((struct sockaddr *)&in, sizeof(struct
               sockaddr_in), dst, cnt, NULL, 0, NI_NUMERICHOST);
      return dst;
   }
#if defined(AF_INET6) && !defined(HAVE_SOCKET_LEGACY)
   else if (af == AF_INET6)
   {
      struct sockaddr_in6 in;
      memset(&in, 0, sizeof(in));
      in.sin6_family = AF_INET6;
      memcpy(&in.sin6_addr, src, sizeof(struct in_addr6_compat));
      getnameinfo((struct sockaddr *)&in, sizeof(struct
               sockaddr_in6), dst, cnt, NULL, 0, NI_NUMERICHOST);
      return dst;
   }
#endif
   else
      return NULL;
#else
   return inet_ntop(af, src, dst, cnt);
#endif
}