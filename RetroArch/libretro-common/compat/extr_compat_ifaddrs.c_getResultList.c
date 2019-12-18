#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nlmsghdr {int dummy; } ;
struct TYPE_5__ {struct TYPE_5__* m_next; } ;
typedef  TYPE_1__ NetlinkList ;

/* Variables and functions */
 int /*<<< orphan*/  freeResultList (TYPE_1__*) ; 
 struct nlmsghdr* getNetlinkResponse (int,int*,int*) ; 
 scalar_t__ netlink_send (int,int) ; 
 TYPE_1__* newListItem (struct nlmsghdr*,int) ; 

__attribute__((used)) static NetlinkList *getResultList(int p_socket, int p_request)
{
   if(netlink_send(p_socket, p_request) < 0)
      return NULL;

   NetlinkList *l_list = NULL;
   NetlinkList *l_end = NULL;
   int l_size;
   int l_done = 0;
   while(!l_done)
   {
      NetlinkList *l_item    = NULL;
      struct nlmsghdr *l_hdr = getNetlinkResponse(p_socket, &l_size, &l_done);
      if(!l_hdr)
         goto error;

      l_item = newListItem(l_hdr, l_size);
      if (!l_item)
         goto error;

      if(!l_list)
         l_list = l_item;
      else
         l_end->m_next = l_item;
      l_end = l_item;
   }

   return l_list;

error:
   freeResultList(l_list);
   return NULL;
}