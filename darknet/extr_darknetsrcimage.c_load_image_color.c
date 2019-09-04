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
 int /*<<< orphan*/  load_image (char*,int,int,int) ; 

image load_image_color(char *filename, int w, int h)
{
    return load_image(filename, w, h, 3);
}