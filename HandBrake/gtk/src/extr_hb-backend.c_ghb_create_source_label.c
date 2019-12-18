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
struct TYPE_3__ {scalar_t__* name; scalar_t__ type; int /*<<< orphan*/  playlist; } ;
typedef  TYPE_1__ hb_title_t ;
typedef  char gchar ;

/* Variables and functions */
 scalar_t__ HB_BD_TYPE ; 
 scalar_t__ HB_DVD_TYPE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dvd_sanitize_volname (char*) ; 
 char* strdup (scalar_t__*) ; 

gchar*
ghb_create_source_label(const hb_title_t * title)
{
    char * volname;
    char * source;

    if (title != NULL && title->name != NULL && title->name[0] != 0)
    {
        volname = strdup(title->name);
        if (title->type == HB_DVD_TYPE)
        {
            ghb_dvd_sanitize_volname(volname);
        }
        if (title->type == HB_BD_TYPE)
        {
            source = g_strdup_printf(_("%s - (%05d.MPLS)"),
                                     volname, title->playlist);
            g_free(volname);
        }
        else
        {
            source = volname;
        }
    }
    else
    {
        source = g_strdup(_("No Title Found"));
    }
    return source;
}