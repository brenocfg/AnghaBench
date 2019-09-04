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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ matrix ;

/* Variables and functions */
 int /*<<< orphan*/  fill_hierarchy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_truth (char*,char**,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ make_matrix (int,int) ; 

matrix load_labels_paths(char **paths, int n, char **labels, int k, tree *hierarchy)
{
    matrix y = make_matrix(n, k);
    int i;
    for(i = 0; i < n && labels; ++i){
        fill_truth(paths[i], labels, k, y.vals[i]);
        if(hierarchy){
            fill_hierarchy(y.vals[i], k, hierarchy);
        }
    }
    return y;
}