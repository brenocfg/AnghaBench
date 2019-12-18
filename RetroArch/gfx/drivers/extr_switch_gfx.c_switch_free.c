#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  vsync_h; } ;
typedef  TYPE_1__ switch_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  display_close_layer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_finalize () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  svcCloseHandle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switch_free(void *data)
{
	switch_video_t *sw = data;
	svcCloseHandle(sw->vsync_h);
	display_close_layer(&sw->surface);
	display_finalize();
	free(sw);
}