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
struct TYPE_4__ {scalar_t__ code; scalar_t__ handler; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ext_int_info_t ;
typedef  scalar_t__ ext_int_handler_t ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int ENOENT ; 
 int ext_hash (scalar_t__) ; 
 TYPE_1__** ext_int_hash ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

int unregister_external_interrupt(__u16 code, ext_int_handler_t handler)
{
        ext_int_info_t *p, *q;
        int index;

	index = ext_hash(code);
        q = NULL;
        p = ext_int_hash[index];
        while (p != NULL) {
                if (p->code == code && p->handler == handler)
                        break;
                q = p;
                p = p->next;
        }
        if (p == NULL)
                return -ENOENT;
        if (q != NULL)
                q->next = p->next;
        else
                ext_int_hash[index] = p->next;
	kfree(p);
        return 0;
}