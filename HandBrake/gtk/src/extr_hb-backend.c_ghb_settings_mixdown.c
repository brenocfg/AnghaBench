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
typedef  int /*<<< orphan*/  hb_mixdown_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 char* ghb_dict_get_string (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  const* ghb_lookup_mixdown (char const*) ; 

const hb_mixdown_t*
ghb_settings_mixdown(const GhbValue *settings, const char *name)
{
    const char *mixdown_id = ghb_dict_get_string(settings, name);
    return ghb_lookup_mixdown(mixdown_id);
}