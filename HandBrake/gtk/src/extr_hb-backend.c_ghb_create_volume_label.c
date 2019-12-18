#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* name; scalar_t__ type; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ hb_title_t ;
typedef  char gchar ;
struct TYPE_6__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__ GStatBuf ;

/* Variables and functions */
 scalar_t__ HB_DVD_TYPE ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  camel_convert (char*) ; 
 scalar_t__ g_stat (int /*<<< orphan*/ ,TYPE_2__*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 char* get_file_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dvd_sanitize_volname (char*) ; 
 char* strdup (scalar_t__*) ; 
 scalar_t__ uppers_and_unders (char*) ; 

gchar*
ghb_create_volume_label(const hb_title_t * title)
{
    char * volname = NULL;

    if (title != NULL && title->name != NULL && title->name[0] != 0)
    {
        GStatBuf stat_buf;

        if (g_stat(title->path, &stat_buf) == 0)
        {
            if (!S_ISBLK(stat_buf.st_mode))
            {
                volname = get_file_label(title->path);
            }
            else
            {
                // DVD and BD volume labels are often all upper case
                volname = strdup(title->name);
                if (title->type == HB_DVD_TYPE)
                {
                    ghb_dvd_sanitize_volname(volname);
                }
                if (uppers_and_unders(volname))
                {
                    camel_convert(volname);
                }
            }
        }
        if (volname == NULL)
        {
            volname = strdup(title->name);
            if (title->type == HB_DVD_TYPE)
            {
                ghb_dvd_sanitize_volname(volname);
            }
        }
    }
    else
    {
        volname = g_strdup(_("No Title Found"));
    }
    return volname;
}