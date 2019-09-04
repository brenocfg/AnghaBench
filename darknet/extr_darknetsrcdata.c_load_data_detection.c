#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {float w; float h; int /*<<< orphan*/  data; int /*<<< orphan*/  c; } ;
typedef  TYPE_2__ image ;
struct TYPE_17__ {int /*<<< orphan*/ * vals; } ;
struct TYPE_14__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_16__ {TYPE_7__ y; TYPE_1__ X; scalar_t__ shallow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ data ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  fill_image (TYPE_2__,double) ; 
 int /*<<< orphan*/  fill_truth_detection (char*,int,int /*<<< orphan*/ ,int,int,float,float,float,float) ; 
 int /*<<< orphan*/  flip_image (TYPE_2__) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  free_image (TYPE_2__) ; 
 char** get_random_paths (char**,int,int) ; 
 TYPE_2__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ make_image (int,int,int /*<<< orphan*/ ) ; 
 TYPE_7__ make_matrix (int,int) ; 
 int /*<<< orphan*/  place_image (TYPE_2__,float,float,float,float,TYPE_2__) ; 
 int rand () ; 
 float rand_uniform (float,int) ; 
 int /*<<< orphan*/  random_distort_image (TYPE_2__,float,float,float) ; 

data load_data_detection(int n, char **paths, int m, int w, int h, int boxes, int classes, float jitter, float hue, float saturation, float exposure)
{
    char **random_paths = get_random_paths(paths, n, m);
    int i;
    data d = {0};
    d.shallow = 0;

    d.X.rows = n;
    d.X.vals = calloc(d.X.rows, sizeof(float*));
    d.X.cols = h*w*3;

    d.y = make_matrix(n, 5*boxes);
    for(i = 0; i < n; ++i){
        image orig = load_image_color(random_paths[i], 0, 0);
        image sized = make_image(w, h, orig.c);
        fill_image(sized, .5);

        float dw = jitter * orig.w;
        float dh = jitter * orig.h;

        float new_ar = (orig.w + rand_uniform(-dw, dw)) / (orig.h + rand_uniform(-dh, dh));
        //float scale = rand_uniform(.25, 2);
        float scale = 1;

        float nw, nh;

        if(new_ar < 1){
            nh = scale * h;
            nw = nh * new_ar;
        } else {
            nw = scale * w;
            nh = nw / new_ar;
        }

        float dx = rand_uniform(0, w - nw);
        float dy = rand_uniform(0, h - nh);

        place_image(orig, nw, nh, dx, dy, sized);

        random_distort_image(sized, hue, saturation, exposure);

        int flip = rand()%2;
        if(flip) flip_image(sized);
        d.X.vals[i] = sized.data;


        fill_truth_detection(random_paths[i], boxes, d.y.vals[i], classes, flip, -dx/w, -dy/h, nw/w, nh/h);

        free_image(orig);
    }
    free(random_paths);
    return d;
}