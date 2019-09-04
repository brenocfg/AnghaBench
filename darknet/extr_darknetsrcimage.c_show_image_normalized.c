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
 int /*<<< orphan*/  copy_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_image (int /*<<< orphan*/ ,char const*,int) ; 

void show_image_normalized(image im, const char *name)
{
    image c = copy_image(im);
    normalize_image(c);
    show_image(c, name, 1);
    free_image(c);
}