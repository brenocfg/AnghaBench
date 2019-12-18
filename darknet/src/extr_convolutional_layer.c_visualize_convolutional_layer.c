#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  image ;
struct TYPE_5__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ convolutional_layer ;

/* Variables and functions */
 int /*<<< orphan*/  collapse_image_layers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_convolutional_image (TYPE_1__) ; 
 int /*<<< orphan*/ * get_weights (TYPE_1__) ; 
 int /*<<< orphan*/  show_images (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

image *visualize_convolutional_layer(convolutional_layer l, char *window, image *prev_weights)
{
    image *single_weights = get_weights(l);
    show_images(single_weights, l.n, window);

    image delta = get_convolutional_image(l);
    image dc = collapse_image_layers(delta, 1);
    char buff[256];
    sprintf(buff, "%s: Output", window);
    //show_image(dc, buff);
    //save_image(dc, buff);
    free_image(dc);
    return single_weights;
}