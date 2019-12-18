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
typedef  int /*<<< orphan*/  signal_user_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  audio_refresh_list_ui (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_sanitize_audio_tracks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_update_summary_info (int /*<<< orphan*/ *) ; 

void
ghb_audio_list_refresh_all(signal_user_data_t *ud)
{
    ghb_sanitize_audio_tracks(ud);
    audio_refresh_list_ui(ud);
    ghb_update_summary_info(ud);
}