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
 int /*<<< orphan*/  hb_video_encoder_get_from_name (char const*) ; 
 char const* hb_video_encoder_get_name (int /*<<< orphan*/ ) ; 

const char* hb_video_encoder_sanitize_name(const char *name)
{
    return hb_video_encoder_get_name(hb_video_encoder_get_from_name(name));
}