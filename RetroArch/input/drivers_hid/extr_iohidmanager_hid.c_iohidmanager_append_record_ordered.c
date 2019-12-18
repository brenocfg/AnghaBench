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
struct TYPE_4__ {scalar_t__ id; struct TYPE_4__* next; } ;
typedef  TYPE_1__ apple_input_rec_t ;

/* Variables and functions */

__attribute__((used)) static void iohidmanager_append_record_ordered(apple_input_rec_t **p_rec, apple_input_rec_t *b)
{
    apple_input_rec_t *tmp = *p_rec;
    while (tmp && (tmp->id <= b->id))
    {
       p_rec = &tmp->next;
       tmp   = tmp->next;
    }
    b->next  = tmp;
    *p_rec   = b;
}