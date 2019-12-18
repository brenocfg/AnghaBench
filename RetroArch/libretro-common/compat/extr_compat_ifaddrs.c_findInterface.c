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
struct ifaddrs {struct ifaddrs* ifa_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 

__attribute__((used)) static struct ifaddrs *findInterface(int p_index, struct ifaddrs **p_links, int p_numLinks)
{
   int l_num = 0;
   struct ifaddrs *l_cur = *p_links;
   while(l_cur && l_num < p_numLinks)
   {
      int l_index;
      char *l_indexPtr = ((char *)l_cur) + sizeof(struct ifaddrs);

      memcpy(&l_index, l_indexPtr, sizeof(int));
      if(l_index == p_index)
         return l_cur;

      l_cur = l_cur->ifa_next;
      ++l_num;
   }
   return NULL;
}