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
typedef  int /*<<< orphan*/  hb_encoder_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 char* ghb_dict_get_string (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  const* ghb_lookup_video_encoder (char const*) ; 

const hb_encoder_t*
ghb_settings_video_encoder(const GhbValue *settings, const char *name)
{
    const char *encoder_id = ghb_dict_get_string(settings, name);
    return ghb_lookup_video_encoder(encoder_id);
}