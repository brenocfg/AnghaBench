#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {double h; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 TYPE_1__ border_image (TYPE_1__,double) ; 
 int /*<<< orphan*/  free_image (TYPE_1__) ; 
 TYPE_1__ make_empty_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ tile_images (TYPE_1__,TYPE_1__,int) ; 

image get_label(image **characters, char *string, int size)
{
    size = size/10;
    if(size > 7) size = 7;
    image label = make_empty_image(0,0,0);
    while(*string){
        image l = characters[size][(int)*string];
        image n = tile_images(label, l, -size - 1 + (size+1)/2);
        free_image(label);
        label = n;
        ++string;
    }
    image b = border_image(label, label.h*.25);
    free_image(label);
    return b;
}