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
 int /*<<< orphan*/  JPG ; 
 int /*<<< orphan*/  save_image_options (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 

void save_image(image im, const char *name)
{
    save_image_options(im, name, JPG, 80);
}