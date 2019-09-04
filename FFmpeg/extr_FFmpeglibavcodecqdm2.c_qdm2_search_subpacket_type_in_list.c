#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__* packet; } ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_2__ QDM2SubPNode ;

/* Variables and functions */

__attribute__((used)) static QDM2SubPNode *qdm2_search_subpacket_type_in_list(QDM2SubPNode *list,
                                                        int type)
{
    while (list && list->packet) {
        if (list->packet->type == type)
            return list;
        list = list->next;
    }
    return NULL;
}