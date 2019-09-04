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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int w; int h; int /*<<< orphan*/  y; int /*<<< orphan*/  X; scalar_t__ shallow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int /*<<< orphan*/  free (char**) ; 
 char** get_random_paths (char**,int,int) ; 
 int /*<<< orphan*/  load_image_augment_paths (char**,int,int,int,int,float,float,float,float,float,int) ; 
 int /*<<< orphan*/  load_labels_paths (char**,int,char**,int,int /*<<< orphan*/ *) ; 

data load_data_augment(char **paths, int n, int m, char **labels, int k, tree *hierarchy, int min, int max, int size, float angle, float aspect, float hue, float saturation, float exposure, int center)
{
    if(m) paths = get_random_paths(paths, n, m);
    data d = {0};
    d.shallow = 0;
    d.w=size;
    d.h=size;
    d.X = load_image_augment_paths(paths, n, min, max, size, angle, aspect, hue, saturation, exposure, center);
    d.y = load_labels_paths(paths, n, labels, k, hierarchy);
    if(m) free(paths);
    return d;
}