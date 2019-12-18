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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  curl_socklen_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  Curl_inet_ntop (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int FALSE ; 
 int /*<<< orphan*/  MAX_IPADR_LEN ; 
 int TRUE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 

bool Curl_addr2string(struct sockaddr *sa, curl_socklen_t salen,
                      char *addr, long *port)
{
  struct sockaddr_in *si = NULL;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 *si6 = NULL;
#endif
#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)
  struct sockaddr_un *su = NULL;
#else
  (void)salen;
#endif

  switch(sa->sa_family) {
    case AF_INET:
      si = (struct sockaddr_in *)(void *) sa;
      if(Curl_inet_ntop(sa->sa_family, &si->sin_addr,
                        addr, MAX_IPADR_LEN)) {
        unsigned short us_port = ntohs(si->sin_port);
        *port = us_port;
        return TRUE;
      }
      break;
#ifdef ENABLE_IPV6
    case AF_INET6:
      si6 = (struct sockaddr_in6 *)(void *) sa;
      if(Curl_inet_ntop(sa->sa_family, &si6->sin6_addr,
                        addr, MAX_IPADR_LEN)) {
        unsigned short us_port = ntohs(si6->sin6_port);
        *port = us_port;
        return TRUE;
      }
      break;
#endif
#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)
    case AF_UNIX:
      if(salen > (curl_socklen_t)sizeof(sa_family_t)) {
        su = (struct sockaddr_un*)sa;
        msnprintf(addr, MAX_IPADR_LEN, "%s", su->sun_path);
      }
      else
        addr[0] = 0; /* socket with no name */
      *port = 0;
      return TRUE;
#endif
    default:
      break;
  }

  addr[0] = '\0';
  *port = 0;
  errno = EAFNOSUPPORT;
  return FALSE;
}