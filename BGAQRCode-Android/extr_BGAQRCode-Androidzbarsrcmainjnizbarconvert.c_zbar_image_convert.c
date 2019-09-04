#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */
 TYPE_1__* zbar_image_convert_resize (TYPE_1__ const*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

zbar_image_t *zbar_image_convert (const zbar_image_t *src,
                                  unsigned long fmt)
{
    return(zbar_image_convert_resize(src, fmt, src->width, src->height));
}