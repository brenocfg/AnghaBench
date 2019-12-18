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
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void list_free(list_t *list)
{
    if (!list) {
        return;
    }

    list_clear(list);
    osi_free(list);
}