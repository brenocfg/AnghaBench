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
struct TYPE_4__ {int dim; int /*<<< orphan*/ * points; TYPE_2__** cells; } ;
typedef  TYPE_1__ elbg_data ;
struct TYPE_5__ {int index; struct TYPE_5__* next; } ;
typedef  TYPE_2__ cell ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int INT_MAX ; 

__attribute__((used)) static void get_new_centroids(elbg_data *elbg, int huc, int *newcentroid_i,
                              int *newcentroid_p)
{
    cell *tempcell;
    int *min = newcentroid_i;
    int *max = newcentroid_p;
    int i;

    for (i=0; i< elbg->dim; i++) {
        min[i]=INT_MAX;
        max[i]=0;
    }

    for (tempcell = elbg->cells[huc]; tempcell; tempcell = tempcell->next)
        for(i=0; i<elbg->dim; i++) {
            min[i]=FFMIN(min[i], elbg->points[tempcell->index*elbg->dim + i]);
            max[i]=FFMAX(max[i], elbg->points[tempcell->index*elbg->dim + i]);
        }

    for (i=0; i<elbg->dim; i++) {
        int ni = min[i] + (max[i] - min[i])/3;
        int np = min[i] + (2*(max[i] - min[i]))/3;
        newcentroid_i[i] = ni;
        newcentroid_p[i] = np;
    }
}