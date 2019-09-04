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
struct TYPE_5__ {int dim; scalar_t__ points; } ;
typedef  TYPE_1__ elbg_data ;
struct TYPE_6__ {int index; struct TYPE_6__* next; } ;
typedef  TYPE_2__ cell ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ distance_limited (int*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eval_error_cell(elbg_data *elbg, int *centroid, cell *cells)
{
    int error=0;
    for (; cells; cells=cells->next)
        error += distance_limited(centroid, elbg->points + cells->index*elbg->dim, elbg->dim, INT_MAX);

    return error;
}