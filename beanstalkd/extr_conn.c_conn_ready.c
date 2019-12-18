#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_8__ {TYPE_1__ ready; } ;
typedef  TYPE_3__ Tube ;
struct TYPE_7__ {size_t len; scalar_t__* items; } ;
struct TYPE_9__ {TYPE_2__ watch; } ;
typedef  TYPE_4__ Conn ;

/* Variables and functions */

int
conn_ready(Conn *c)
{
    size_t i;

    for (i = 0; i < c->watch.len; i++) {
        if (((Tube *) c->watch.items[i])->ready.len)
            return 1;
    }
    return 0;
}