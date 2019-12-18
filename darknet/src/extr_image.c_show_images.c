#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  image ;

/* Variables and functions */
 int /*<<< orphan*/  collapse_images_vert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_image (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_image (int /*<<< orphan*/ ,char*,int) ; 

void show_images(image *ims, int n, char *window)
{
    image m = collapse_images_vert(ims, n);
    /*
       int w = 448;
       int h = ((float)m.h/m.w) * 448;
       if(h > 896){
       h = 896;
       w = ((float)m.w/m.h) * 896;
       }
       image sized = resize_image(m, w, h);
     */
    normalize_image(m);
    save_image(m, window);
    show_image(m, window, 1);
    free_image(m);
}