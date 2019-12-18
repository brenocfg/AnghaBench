#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {int ai_flags; int ai_addrlen; struct sockaddr* ai_addr; TYPE_1__ sin_addr; void* sin_family; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  ai_socktype; void* ai_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {char const** h_addr_list; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; void* h_addrtype; } ;
struct addrinfo {int ai_flags; int ai_addrlen; struct sockaddr* ai_addr; TYPE_1__ sin_addr; void* sin_family; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  ai_socktype; void* ai_family; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_UNSPEC ; 
 int AI_PASSIVE ; 
 void* INADDR_ANY ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct sockaddr_in*) ; 
 int getaddrinfo (char const*,char const*,struct sockaddr_in*,struct sockaddr_in**) ; 
 scalar_t__ gethostbyname (char const*) ; 
 void* inet_addr (char const*) ; 
 int /*<<< orphan*/  inet_htons (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int getaddrinfo_retro(const char *node, const char *service,
      struct addrinfo *hints, struct addrinfo **res)
{
   struct sockaddr_in *in_addr = NULL;
   struct addrinfo *info       = NULL;

   (void)in_addr;
   (void)info;

   if (!hints->ai_family)
   {
#if defined(_WIN32) || defined(HAVE_SOCKET_LEGACY) || defined(WIIU)
      hints->ai_family    = AF_INET;
#else
      hints->ai_family    = AF_UNSPEC;
#endif
   }

#if defined(WIIU)
   if (!node)
   {
      /* Wii U's socket library chokes on NULL node */
      if (hints->ai_flags & AI_PASSIVE)
         node = "0.0.0.0";
      else
         node = "127.0.0.1";
   }
#endif

#ifdef HAVE_SOCKET_LEGACY
   info = (struct addrinfo*)calloc(1, sizeof(*info));
   if (!info)
      goto error;

   info->ai_family     = AF_INET;
   info->ai_socktype   = hints->ai_socktype;
   in_addr             = (struct sockaddr_in*)
      calloc(1, sizeof(*in_addr));

   if (!in_addr)
      goto error;

   info->ai_addrlen    = sizeof(*in_addr);
   in_addr->sin_family = AF_INET;
   in_addr->sin_port   = inet_htons(strtoul(service, NULL, 0));

   if (!node && (hints->ai_flags & AI_PASSIVE))
      in_addr->sin_addr.s_addr = INADDR_ANY;
   else if (node && isdigit(*node))
      in_addr->sin_addr.s_addr = inet_addr(node);
   else if (node && !isdigit(*node))
   {
      struct hostent *host = (struct hostent*)gethostbyname(node);

      if (!host || !host->h_addr_list[0])
         goto error;

      in_addr->sin_family = host->h_addrtype;

#if defined(AF_INET6) && !defined(__CELLOS_LV2__) || defined(VITA)
      /* TODO/FIXME - In case we ever want to support IPv6 */
      in_addr->sin_addr.s_addr = inet_addr(host->h_addr_list[0]);
#else
      memcpy(&in_addr->sin_addr, host->h_addr, host->h_length);
#endif
   }
   else
      goto error;

   info->ai_addr = (struct sockaddr*)in_addr;
   *res          = info;

   return 0;

error:
   if (in_addr)
      free(in_addr);
   if (info)
      free(info);
   return -1;
#else
   return getaddrinfo(node, service, hints, res);
#endif
}