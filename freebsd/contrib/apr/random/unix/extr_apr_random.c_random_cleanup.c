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
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ apr_random_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 TYPE_1__* all_random ; 

__attribute__((used)) static apr_status_t random_cleanup(void *data)
{
    apr_random_t *remove_this = data,
                 *cur = all_random,
                 **prev_ptr = &all_random;
    while (cur) {
        if (cur == remove_this) {
            *prev_ptr = cur->next;
            break;
        }
        prev_ptr = &cur->next;
        cur = cur->next;
    }
    return APR_SUCCESS;
}