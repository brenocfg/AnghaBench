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

/* Variables and functions */
 int /*<<< orphan*/  layer_fb ; 
 int pnd_setup_layer_ (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  vout_fbdev_get_fd (int /*<<< orphan*/ ) ; 

int pnd_setup_layer(int enabled, int x, int y, int w, int h)
{
	return pnd_setup_layer_(vout_fbdev_get_fd(layer_fb), enabled, x, y, w, h);
}