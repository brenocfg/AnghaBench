#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nlmsghdr {int dummy; } ;
struct TYPE_4__ {unsigned int m_size; struct nlmsghdr* m_data; int /*<<< orphan*/ * m_next; } ;
typedef  TYPE_1__ NetlinkList ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static NetlinkList *newListItem(struct nlmsghdr *p_data, unsigned int p_size)
{
   NetlinkList *l_item = malloc(sizeof(NetlinkList));
   if (l_item == NULL)
      return NULL;

   l_item->m_next = NULL;
   l_item->m_data = p_data;
   l_item->m_size = p_size;
   return l_item;
}