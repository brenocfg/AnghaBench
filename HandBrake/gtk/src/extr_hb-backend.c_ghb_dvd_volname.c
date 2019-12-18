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
typedef  scalar_t__ gchar ;

/* Variables and functions */
 scalar_t__* g_strdup (scalar_t__*) ; 
 int /*<<< orphan*/  ghb_dvd_sanitize_volname (scalar_t__*) ; 
 scalar_t__* hb_dvd_name (scalar_t__*) ; 

gchar*
ghb_dvd_volname(const gchar *device)
{
    gchar *name;
    name = hb_dvd_name((gchar*)device);
    if (name != NULL && name[0] != 0)
    {
        name = g_strdup(name);
        ghb_dvd_sanitize_volname(name);
        return name;
    }
    return NULL;
}