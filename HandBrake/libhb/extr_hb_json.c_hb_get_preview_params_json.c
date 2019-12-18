#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_3__ json_error_t ;
struct TYPE_7__ {int num; int den; } ;
struct TYPE_8__ {int width; int height; TYPE_1__ par; } ;
struct TYPE_10__ {int mode; int keep; int itu_par; int modulus; int maxWidth; int maxHeight; int* crop; TYPE_2__ geometry; } ;
typedef  TYPE_4__ hb_geometry_settings_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_bool (int) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/ * json_pack_ex (TYPE_3__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char* hb_get_preview_params_json(int title_idx, int preview_idx,
                            int deinterlace, hb_geometry_settings_t *settings)
{
    json_error_t error;
    hb_dict_t * dict;

    dict = json_pack_ex(&error, 0,
        "{"
        "s:o, s:o, s:o,"
        "s:{"
        "   s:{s:o, s:o, s:{s:o, s:o}},"
        "   s:o, s:o, s:o, s:o, s:o, s:o"
        "   s:[oooo]"
        "  }"
        "}",
        "Title",                hb_value_int(title_idx),
        "Preview",              hb_value_int(preview_idx),
        "Deinterlace",          hb_value_bool(deinterlace),
        "DestSettings",
            "Geometry",
                "Width",        hb_value_int(settings->geometry.width),
                "Height",       hb_value_int(settings->geometry.height),
                "PAR",
                    "Num",      hb_value_int(settings->geometry.par.num),
                    "Den",      hb_value_int(settings->geometry.par.den),
            "AnamorphicMode",   hb_value_int(settings->mode),
            "Keep",             hb_value_int(settings->keep),
            "ItuPAR",           hb_value_bool(settings->itu_par),
            "Modulus",          hb_value_int(settings->modulus),
            "MaxWidth",         hb_value_int(settings->maxWidth),
            "MaxHeight",        hb_value_int(settings->maxHeight),
            "Crop",             hb_value_int(settings->crop[0]),
                                hb_value_int(settings->crop[1]),
                                hb_value_int(settings->crop[2]),
                                hb_value_int(settings->crop[3])
    );
    if (dict == NULL)
    {
        hb_error("hb_get_preview_params_json: pack failure: %s", error.text);
        return NULL;
    }

    char *result = hb_value_get_json(dict);
    hb_value_free(&dict);

    return result;
}