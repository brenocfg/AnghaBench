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
 int /*<<< orphan*/  MPV_FORMAT_INT64 ; 
 int /*<<< orphan*/  RETRO_LOG_INFO ; 
 int /*<<< orphan*/  log_cb (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpv ; 
 int /*<<< orphan*/  mpv_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpv_gl ; 
 int /*<<< orphan*/  mpv_render_context_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpv_terminate_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playback_time ; 

__attribute__((used)) static void context_destroy(void)
{
	mpv_get_property(mpv, "playback-time", MPV_FORMAT_INT64, &playback_time);
	mpv_render_context_free(mpv_gl);
	mpv_terminate_destroy(mpv);
	log_cb(RETRO_LOG_INFO, "Context destroyed.\n");
}