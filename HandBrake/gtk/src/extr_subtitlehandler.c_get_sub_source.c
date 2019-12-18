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
struct TYPE_5__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_6__ {int source; } ;
typedef  TYPE_2__ hb_subtitle_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int IMPORTSRT ; 
 int IMPORTSSA ; 
 int VOBSUB ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* ghb_lookup_title (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int get_sub_source(GhbValue *settings, GhbValue *subsettings)
{
    GhbValue *import;

    import  = ghb_dict_get(subsettings, "Import");
    if (import != NULL)
    {
        const char * format = ghb_dict_get_string(import, "Format");
        if (format != NULL && !strcasecmp(format, "SSA"))
        {
            return IMPORTSSA;
        }
        return IMPORTSRT;
    }

    int title_id = ghb_dict_get_int(settings, "title");
    const hb_title_t *title = ghb_lookup_title(title_id, NULL);
    if (title == NULL) // No title, scan failure?
        return VOBSUB;

    GhbValue *val = ghb_dict_get(subsettings, "Track");
    if (val == NULL) // No track, foreign audio search
        return VOBSUB;

    int track = ghb_dict_get_int(subsettings, "Track");
    hb_subtitle_t *subtitle = hb_list_item(title->list_subtitle, track);
    if (subtitle != NULL) // Invalid track, shouldn't happen
        return subtitle->source;

    return VOBSUB;
}