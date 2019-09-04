#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ image ;
struct TYPE_14__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_13__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_16__ {TYPE_2__ y; TYPE_1__ X; scalar_t__ shallow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ data ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  flip_image (TYPE_3__) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 char** get_random_paths (char**,int,int) ; 
 TYPE_3__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rand () ; 
 TYPE_3__ random_crop_image (TYPE_3__,int,int) ; 
 TYPE_3__ resize_image (TYPE_3__,int,int) ; 

data load_data_super(char **paths, int n, int m, int w, int h, int scale)
{
    if(m) paths = get_random_paths(paths, n, m);
    data d = {0};
    d.shallow = 0;

    int i;
    d.X.rows = n;
    d.X.vals = calloc(n, sizeof(float*));
    d.X.cols = w*h*3;

    d.y.rows = n;
    d.y.vals = calloc(n, sizeof(float*));
    d.y.cols = w*scale * h*scale * 3;

    for(i = 0; i < n; ++i){
        image im = load_image_color(paths[i], 0, 0);
        image crop = random_crop_image(im, w*scale, h*scale);
        int flip = rand()%2;
        if (flip) flip_image(crop);
        image resize = resize_image(crop, w, h);
        d.X.vals[i] = resize.data;
        d.y.vals[i] = crop.data;
        free_image(im);
    }

    if(m) free(paths);
    return d;
}