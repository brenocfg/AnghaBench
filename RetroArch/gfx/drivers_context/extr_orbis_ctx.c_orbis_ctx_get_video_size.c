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
typedef  int /*<<< orphan*/  orbis_ctx_data_t ;

/* Variables and functions */
 unsigned int ATTR_ORBISGL_HEIGHT ; 
 unsigned int ATTR_ORBISGL_WIDTH ; 

__attribute__((used)) static void orbis_ctx_get_video_size(void *data,
                                      unsigned *width, unsigned *height)
{
    orbis_ctx_data_t *ctx_orbis = (orbis_ctx_data_t *)data;

    *width = ATTR_ORBISGL_WIDTH;
    *height = ATTR_ORBISGL_HEIGHT;
}