#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ image ;
struct TYPE_16__ {int /*<<< orphan*/ * vals; } ;
struct TYPE_17__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_19__ {TYPE_10__ y; TYPE_1__ X; scalar_t__ shallow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ data ;
struct TYPE_20__ {int /*<<< orphan*/  aspect; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  scale; int /*<<< orphan*/  rad; } ;
typedef  TYPE_4__ augment_args ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  fill_truth_mask (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__,int,int,int) ; 
 int /*<<< orphan*/  flip_image (TYPE_2__) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  free_image (TYPE_2__) ; 
 char** get_random_paths (char**,int,int) ; 
 TYPE_2__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__ make_matrix (int,int) ; 
 int rand () ; 
 TYPE_4__ random_augment_args (TYPE_2__,float,float,int,int,int,int) ; 
 int /*<<< orphan*/  random_distort_image (TYPE_2__,float,float,float) ; 
 TYPE_2__ rotate_crop_image (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

data load_data_mask(int n, char **paths, int m, int w, int h, int classes, int boxes, int coords, int min, int max, float angle, float aspect, float hue, float saturation, float exposure)
{
    char **random_paths = get_random_paths(paths, n, m);
    int i;
    data d = {0};
    d.shallow = 0;

    d.X.rows = n;
    d.X.vals = calloc(d.X.rows, sizeof(float*));
    d.X.cols = h*w*3;

    d.y = make_matrix(n, (coords+1)*boxes);

    for(i = 0; i < n; ++i){
        image orig = load_image_color(random_paths[i], 0, 0);
        augment_args a = random_augment_args(orig, angle, aspect, min, max, w, h);
        image sized = rotate_crop_image(orig, a.rad, a.scale, a.w, a.h, a.dx, a.dy, a.aspect);

        int flip = rand()%2;
        if(flip) flip_image(sized);
        random_distort_image(sized, hue, saturation, exposure);
        d.X.vals[i] = sized.data;
        //show_image(sized, "image");

        fill_truth_mask(random_paths[i], boxes, d.y.vals[i], classes, orig.w, orig.h, a, flip, 14, 14);

        free_image(orig);

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