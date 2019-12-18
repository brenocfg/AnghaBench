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
struct TYPE_6__ {int id; } ;
struct TYPE_5__ {int count; TYPE_2__* object; } ;
typedef  TYPE_1__ PGSSubObjects ;
typedef  TYPE_2__ PGSSubObject ;

/* Variables and functions */

__attribute__((used)) static PGSSubObject * find_object(int id, PGSSubObjects *objects)
{
    int i;

    for (i = 0; i < objects->count; i++) {
        if (objects->object[i].id == id)
            return &objects->object[i];
    }
    return NULL;
}