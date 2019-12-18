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
struct ifaddrs {int dummy; } ;
typedef  int /*<<< orphan*/  NetlinkList ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_GETADDR ; 
 int /*<<< orphan*/  RTM_GETLINK ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  freeResultList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getResultList (int,int /*<<< orphan*/ ) ; 
 int interpretAddrs (int,int /*<<< orphan*/ *,struct ifaddrs**,int) ; 
 int interpretLinks (int,int /*<<< orphan*/ *,struct ifaddrs**) ; 
 int netlink_socket () ; 

int getifaddrs(struct ifaddrs **ifap)
{
   int l_socket = 0;
   int l_result = 0;
   if(!ifap)
      return -1;
   *ifap = NULL;

   l_socket = netlink_socket();
   if(l_socket < 0)
      return -1;

   NetlinkList *l_linkResults = getResultList(l_socket, RTM_GETLINK);
   if(!l_linkResults)
   {
      close(l_socket);
      return -1;
   }

   NetlinkList *l_addrResults = getResultList(l_socket, RTM_GETADDR);
   if(!l_addrResults)
   {
      close(l_socket);
      freeResultList(l_linkResults);
      return -1;
   }

   int l_numLinks = interpretLinks(l_socket, l_linkResults, ifap);

   if(l_numLinks == -1 || interpretAddrs(l_socket, l_addrResults, ifap, l_numLinks) == -1)
      l_result = -1;

   freeResultList(l_linkResults);
   freeResultList(l_addrResults);
   close(l_socket);
   return l_result;
}