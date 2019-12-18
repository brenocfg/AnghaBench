#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int depth; } ;
typedef  TYPE_1__ hb_preset_index_t ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_markup_escape_text (char const*,int) ; 
 int /*<<< orphan*/  g_string_append (int /*<<< orphan*/ *,char const*) ; 
 char* g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_preset_get (TYPE_1__*) ; 
 TYPE_1__* hb_preset_index_dup (TYPE_1__*) ; 

char*
preset_get_fullname(hb_preset_index_t *path, const char * sep, gboolean escape)
{
    int                ii;
    GString           *gstr;
    hb_preset_index_t *tmp;
    GhbValue          *dict;

    gstr = g_string_new("");
    tmp  = hb_preset_index_dup(path);
    for (ii = 1; ii <= path->depth; ii++)
    {
        const char *name;
        tmp->depth = ii;
        dict = hb_preset_get(tmp);
        if (dict == NULL)
        {
            break;
        }
        name = ghb_dict_get_string(dict, "PresetName");
        if (name != NULL)
        {
            g_string_append(gstr, sep);
            if (escape)
            {
                char * esc = g_markup_escape_text(name, -1);
                g_string_append(gstr, esc);
                g_free(esc);
            }
            else
            {
                g_string_append(gstr, name);
            }
        }
    }
    free(tmp);
    char *str = g_string_free(gstr, FALSE);
    return str;
}