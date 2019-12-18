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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int hb_video_encoder_get_from_name (char const*) ; 

int ghb_get_video_encoder(GhbValue *settings)
{
    const char *encoder;
    encoder = ghb_dict_get_string(settings, "VideoEncoder");
    return hb_video_encoder_get_from_name(encoder);
}