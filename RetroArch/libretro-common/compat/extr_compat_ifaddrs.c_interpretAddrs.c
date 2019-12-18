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
struct nlmsghdr {scalar_t__ nlmsg_type; scalar_t__ nlmsg_seq; scalar_t__ nlmsg_pid; } ;
struct ifaddrs {int dummy; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {unsigned int m_size; struct nlmsghdr* m_data; struct TYPE_3__* m_next; } ;
typedef  TYPE_1__ NetlinkList ;

/* Variables and functions */
 scalar_t__ NLMSG_DONE ; 
 struct nlmsghdr* NLMSG_NEXT (struct nlmsghdr*,unsigned int) ; 
 scalar_t__ NLMSG_OK (struct nlmsghdr*,unsigned int) ; 
 scalar_t__ RTM_NEWADDR ; 
 scalar_t__ getpid () ; 
 int interpretAddr (struct nlmsghdr*,struct ifaddrs**,int) ; 

__attribute__((used)) static int interpretAddrs(int p_socket, NetlinkList *p_netlinkList,
      struct ifaddrs **p_resultList, int p_numLinks)
{
   pid_t l_pid = getpid();
   for(; p_netlinkList; p_netlinkList = p_netlinkList->m_next)
   {
      struct nlmsghdr *l_hdr = NULL;
      unsigned int l_nlsize  = p_netlinkList->m_size;

      for(l_hdr = p_netlinkList->m_data; NLMSG_OK(l_hdr, l_nlsize); l_hdr = NLMSG_NEXT(l_hdr, l_nlsize))
      {
         if((pid_t)l_hdr->nlmsg_pid != l_pid || (int)l_hdr->nlmsg_seq != p_socket)
            continue;

         if(l_hdr->nlmsg_type == NLMSG_DONE)
            break;

         if(l_hdr->nlmsg_type == RTM_NEWADDR)
         {
            if (interpretAddr(l_hdr, p_resultList, p_numLinks) == -1)
               return -1;
         }
      }
   }
   return 0;
}