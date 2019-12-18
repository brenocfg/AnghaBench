#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  data; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_3__ image ;
struct TYPE_17__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_16__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_19__ {TYPE_2__ y; TYPE_1__ X; scalar_t__ shallow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ data ;
struct TYPE_20__ {int scale; int w; int h; int dx; int dy; int /*<<< orphan*/  aspect; int /*<<< orphan*/  rad; } ;
typedef  TYPE_5__ augment_args ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  flip_image (TYPE_3__) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  free_image (TYPE_3__) ; 
 char** get_random_paths (char**,int,int) ; 
 TYPE_3__ get_segmentation_image (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rand () ; 
 TYPE_5__ random_augment_args (TYPE_3__,float,float,int,int,int,int) ; 
 int /*<<< orphan*/  random_distort_image (TYPE_3__,float,float,float) ; 
 TYPE_3__ rotate_crop_image (TYPE_3__,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ) ; 

data load_data_seg(int n, char **paths, int m, int w, int h, int classes, int min, int max, float angle, float aspect, float hue, float saturation, float exposure, int div)
{
    char **random_paths = get_random_paths(paths, n, m);
    int i;
    data d = {0};
    d.shallow = 0;

    d.X.rows = n;
    d.X.vals = calloc(d.X.rows, sizeof(float*));
    d.X.cols = h*w*3;


    d.y.rows = n;
    d.y.cols = h*w*classes/div/div;
    d.y.vals = calloc(d.X.rows, sizeof(float*));

    for(i = 0; i < n; ++i){
        image orig = load_image_color(random_paths[i], 0, 0);
        augment_args a = random_augment_args(orig, angle, aspect, min, max, w, h);
        image sized = rotate_crop_image(orig, a.rad, a.scale, a.w, a.h, a.dx, a.dy, a.aspect);

        int flip = rand()%2;
        if(flip) flip_image(sized);
        random_distort_image(sized, hue, saturation, exposure);
        d.X.vals[i] = sized.data;

        image mask = get_segmentation_image(random_paths[i], orig.w, orig.h, classes);
        //image mask = make_image(orig.w, orig.h, classes+1);
        image sized_m = rotate_crop_image(mask, a.rad, a.scale/div, a.w/div, a.h/div, a.dx/div, a.dy/div, a.aspect);

        if(flip) flip_image(sized_m);
        d.y.vals[i] = sized_m.data;

        free_image(orig);
        free_image(mask);

        /*
           image rgb = mask_to_rgb(sized_m, classes);
           show_image(rgb, "part");
           show_image(sized, "orig");
           cvWaitKey(0);
           free_image(rgb);
         */
    }
    free(random_paths);
    return d;
}