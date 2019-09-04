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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

__attribute__((used)) static void dxva2_pool_release_dummy(void *opaque, uint8_t *data)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}