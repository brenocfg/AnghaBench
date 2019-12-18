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
struct TYPE_15__ {int h; int w; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ image ;
struct TYPE_17__ {int /*<<< orphan*/ * vals; } ;
struct TYPE_14__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_16__ {TYPE_7__ y; TYPE_1__ X; scalar_t__ shallow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ data ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 TYPE_2__ crop_image (TYPE_2__,int,int,int,int) ; 
 int /*<<< orphan*/  fill_truth_region (char*,int /*<<< orphan*/ ,int,int,int,float,float,int,int) ; 
 int /*<<< orphan*/  flip_image (TYPE_2__) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  free_image (TYPE_2__) ; 
 char** get_random_paths (char**,int,int) ; 
 TYPE_2__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ make_matrix (int,int) ; 
 int rand () ; 
 int rand_uniform (int,int) ; 
 int /*<<< orphan*/  random_distort_image (TYPE_2__,float,float,float) ; 
 TYPE_2__ resize_image (TYPE_2__,int,int) ; 

data load_data_region(int n, char **paths, int m, int w, int h, int size, int classes, float jitter, float hue, float saturation, float exposure)
{
    char **random_paths = get_random_paths(paths, n, m);
    int i;
    data d = {0};
    d.shallow = 0;

    d.X.rows = n;
    d.X.vals = calloc(d.X.rows, sizeof(float*));
    d.X.cols = h*w*3;


    int k = size*size*(5+classes);
    d.y = make_matrix(n, k);
    for(i = 0; i < n; ++i){
        image orig = load_image_color(random_paths[i], 0, 0);

        int oh = orig.h;
        int ow = orig.w;

        int dw = (ow*jitter);
        int dh = (oh*jitter);

        int pleft  = rand_uniform(-dw, dw);
        int pright = rand_uniform(-dw, dw);
        int ptop   = rand_uniform(-dh, dh);
        int pbot   = rand_uniform(-dh, dh);

        int swidth =  ow - pleft - pright;
        int sheight = oh - ptop - pbot;

        float sx = (float)swidth  / ow;
        float sy = (float)sheight / oh;

        int flip = rand()%2;
        image cropped = crop_image(orig, pleft, ptop, swidth, sheight);

        float dx = ((float)pleft/ow)/sx;
        float dy = ((float)ptop /oh)/sy;

        image sized = resize_image(cropped, w, h);
        if(flip) flip_image(sized);
        random_distort_image(sized, hue, saturation, exposure);
        d.X.vals[i] = sized.data;

        fill_truth_region(random_paths[i], d.y.vals[i], classes, size, flip, dx, dy, 1./sx, 1./sy);

        free_image(orig);
        free_image(cropped);
    }
    free(random_paths);
    return d;
}