#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ matrix ;
struct TYPE_13__ {int h; int w; int c; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ image ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 TYPE_2__ center_crop_image (TYPE_2__,int,int) ; 
 int /*<<< orphan*/  flip_image (TYPE_2__) ; 
 int /*<<< orphan*/  free_image (TYPE_2__) ; 
 TYPE_2__ load_image_color (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rand () ; 
 TYPE_2__ random_augment_image (TYPE_2__,float,float,int,int,int,int) ; 
 int /*<<< orphan*/  random_distort_image (TYPE_2__,float,float,float) ; 

matrix load_image_augment_paths(char **paths, int n, int min, int max, int size, float angle, float aspect, float hue, float saturation, float exposure, int center)
{
    int i;
    matrix X;
    X.rows = n;
    X.vals = calloc(X.rows, sizeof(float*));
    X.cols = 0;

    for(i = 0; i < n; ++i){
        image im = load_image_color(paths[i], 0, 0);
        image crop;
        if(center){
            crop = center_crop_image(im, size, size);
        } else {
            crop = random_augment_image(im, angle, aspect, min, max, size, size);
        }
        int flip = rand()%2;
        if (flip) flip_image(crop);
        random_distort_image(crop, hue, saturation, exposure);

        /*
        show_image(im, "orig");
        show_image(crop, "crop");
        cvWaitKey(0);
        */
        //grayscale_image_3c(crop);
        free_image(im);
        X.vals[i] = crop.data;
        X.cols = crop.h*crop.w*crop.c;
    }
    return X;
}