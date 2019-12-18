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
struct TYPE_4__ {struct TYPE_4__* m_data; struct TYPE_4__* m_next; } ;
typedef  TYPE_1__ NetlinkList ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void freeResultList(NetlinkList *p_list)
{
   NetlinkList *l_cur;
   while(p_list)
   {
      l_cur = p_list;
      p_list = p_list->m_next;
      free(l_cur->m_data);
      free(l_cur);
   }
}