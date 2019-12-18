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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  handler; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ ext_int_info_t ;
typedef  int /*<<< orphan*/  ext_int_handler_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EINVAL ; 
 int ext_hash (int /*<<< orphan*/ ) ; 
 TYPE_1__** ext_int_hash ; 

int register_early_external_interrupt(__u16 code, ext_int_handler_t handler,
				      ext_int_info_t *p)
{
        int index;

        if (p == NULL)
                return -EINVAL;
        p->code = code;
        p->handler = handler;
	index = ext_hash(code);
        p->next = ext_int_hash[index];
        ext_int_hash[index] = p;
        return 0;
}