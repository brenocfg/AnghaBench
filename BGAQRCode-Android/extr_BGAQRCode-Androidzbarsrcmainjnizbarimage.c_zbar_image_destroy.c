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
typedef  int /*<<< orphan*/  zbar_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_image_refcnt (int /*<<< orphan*/ *,int) ; 

void zbar_image_destroy (zbar_image_t *img)
{
    _zbar_image_refcnt(img, -1);
}