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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ EGLNativePixmapType ;

/* Variables and functions */

void platform_get_pixmap_server_handle(EGLNativePixmapType pixmap, uint32_t *handle)
{
   handle[0] = ((uint32_t *)pixmap)[0];
   handle[1] = ((uint32_t *)pixmap)[1];
}