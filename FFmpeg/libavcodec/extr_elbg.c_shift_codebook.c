#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dim; TYPE_2__** cells; scalar_t__ points; } ;
typedef  TYPE_1__ elbg_data ;
struct TYPE_5__ {int index; struct TYPE_5__* next; } ;
typedef  TYPE_2__ cell ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ distance_limited (scalar_t__,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shift_codebook(elbg_data *elbg, int *indexes,
                           int *newcentroid[3])
{
    cell *tempdata;
    cell **pp = &elbg->cells[indexes[2]];

    while(*pp)
        pp= &(*pp)->next;

    *pp = elbg->cells[indexes[0]];

    elbg->cells[indexes[0]] = NULL;
    tempdata = elbg->cells[indexes[1]];
    elbg->cells[indexes[1]] = NULL;

    while(tempdata) {
        cell *tempcell2 = tempdata->next;
        int idx = distance_limited(elbg->points + tempdata->index*elbg->dim,
                           newcentroid[0], elbg->dim, INT_MAX) >
                  distance_limited(elbg->points + tempdata->index*elbg->dim,
                           newcentroid[1], elbg->dim, INT_MAX);

        tempdata->next = elbg->cells[indexes[idx]];
        elbg->cells[indexes[idx]] = tempdata;
        tempdata = tempcell2;
    }
}