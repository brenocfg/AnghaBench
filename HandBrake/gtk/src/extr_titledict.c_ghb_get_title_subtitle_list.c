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
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_get_title_settings (int /*<<< orphan*/ *) ; 

GhbValue *ghb_get_title_subtitle_list(GhbValue *settings)
{
    GhbValue *title_dict = ghb_get_title_settings(settings);
    GhbValue *subtitle_list = ghb_dict_get(title_dict, "SubtitleList");
    return subtitle_list;
}