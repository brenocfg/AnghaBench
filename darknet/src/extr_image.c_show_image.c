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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  save_image (int /*<<< orphan*/ ,char const*) ; 
 int show_image_cv (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

int show_image(image p, const char *name, int ms)
{
#ifdef OPENCV
    int c = show_image_cv(p, name, ms);
    return c;
#else
    fprintf(stderr, "Not compiled with OpenCV, saving to %s.png instead\n", name);
    save_image(p, name);
    return -1;
#endif
}