#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmb_node_t ;
struct TYPE_8__ {TYPE_1__* list; } ;
typedef  TYPE_2__ file_list_t ;
struct TYPE_7__ {int /*<<< orphan*/ * userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_free_actiondata (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  file_list_get_size (TYPE_2__*) ; 
 scalar_t__ file_list_get_userdata_at_offset (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  xmb_free_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xmb_free_list_nodes(file_list_t *list, bool actiondata)
{
   unsigned i, size = (unsigned)file_list_get_size(list);

   for (i = 0; i < size; ++i)
   {
      xmb_free_node((xmb_node_t*)file_list_get_userdata_at_offset(list, i));

      /* file_list_set_userdata() doesn't accept NULL */
      list->list[i].userdata = NULL;

      if (actiondata)
         file_list_free_actiondata(list, i);
   }
}