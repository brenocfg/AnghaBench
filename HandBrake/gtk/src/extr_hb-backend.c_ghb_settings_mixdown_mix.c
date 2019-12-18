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
 char* ghb_dict_get_string (int /*<<< orphan*/  const*,char const*) ; 
 int ghb_lookup_mixdown_mix (char const*) ; 

int
ghb_settings_mixdown_mix(const GhbValue *settings, const char *name)
{
    const char *mixdown_id = ghb_dict_get_string(settings, name);
    return ghb_lookup_mixdown_mix(mixdown_id);
}