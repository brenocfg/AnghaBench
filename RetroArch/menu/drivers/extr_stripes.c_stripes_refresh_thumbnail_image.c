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
 int /*<<< orphan*/  stripes_update_thumbnail_image (void*) ; 

__attribute__((used)) static void stripes_refresh_thumbnail_image(void *data, unsigned i)
{
   stripes_update_thumbnail_image(data);
}