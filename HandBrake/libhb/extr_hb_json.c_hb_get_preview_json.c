#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  settings ;
struct TYPE_16__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_4__ json_error_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_17__ {int format; int width; int height; TYPE_3__* plane; } ;
typedef  TYPE_5__ hb_image_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
struct TYPE_13__ {int num; int den; } ;
struct TYPE_14__ {int width; int height; TYPE_1__ par; } ;
struct TYPE_18__ {int mode; int keep; int itu_par; int modulus; int maxWidth; int maxHeight; int* crop; TYPE_2__ geometry; } ;
typedef  TYPE_6__ hb_geometry_settings_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;
struct TYPE_15__ {int width; int height; int stride; int height_stride; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int AV_BASE64_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_base64_encode (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* hb_get_preview2 (int /*<<< orphan*/ *,int,int,TYPE_6__*,int) ; 
 int /*<<< orphan*/  hb_image_close (TYPE_5__**) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/ * hb_value_json (char const*) ; 
 int /*<<< orphan*/  hb_value_string (char*) ; 
 int /*<<< orphan*/ * json_pack_ex (TYPE_4__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int json_unpack_ex (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unpack_b (int*) ; 
 int /*<<< orphan*/  unpack_i (int*) ; 

char* hb_get_preview_json(hb_handle_t * h, const char *json_param)
{
    hb_image_t *image;
    int ii, title_idx, preview_idx, deinterlace = 0;

    int json_result;
    json_error_t error;
    hb_dict_t * dict;
    hb_geometry_settings_t settings;

    // Clear dest geometry since some fields are optional.
    memset(&settings, 0, sizeof(settings));

    dict = hb_value_json(json_param);
    json_result = json_unpack_ex(dict, &error, 0,
    "{"
    // Title, Preview, Deinterlace
    "s:i, s:i, s?b,"
    // DestSettings
    "s:{"
    //   Geometry {Width, Height, PAR {Num, Den}},
    "s:{s:i, s:i, s:{s:i, s:i}},"
    //   AnamorphicMode, Keep, ItuPAR, Modulus, MaxWidth, MaxHeight,
    "s:i, s?i, s?b, s:i, s:i, s:i,"
    //   Crop [Top, Bottom, Left, Right]
    "s?[iiii]"
    "  }"
    "}",
    "Title",                    unpack_i(&title_idx),
    "Preview",                  unpack_i(&preview_idx),
    "Deinterlace",              unpack_b(&deinterlace),
    "DestSettings",
        "Geometry",
            "Width",            unpack_i(&settings.geometry.width),
            "Height",           unpack_i(&settings.geometry.height),
            "PAR",
                "Num",          unpack_i(&settings.geometry.par.num),
                "Den",          unpack_i(&settings.geometry.par.den),
        "AnamorphicMode",       unpack_i(&settings.mode),
        "Keep",                 unpack_i(&settings.keep),
        "ItuPAR",               unpack_b(&settings.itu_par),
        "Modulus",              unpack_i(&settings.modulus),
        "MaxWidth",             unpack_i(&settings.maxWidth),
        "MaxHeight",            unpack_i(&settings.maxHeight),
        "Crop",                 unpack_i(&settings.crop[0]),
                                unpack_i(&settings.crop[1]),
                                unpack_i(&settings.crop[2]),
                                unpack_i(&settings.crop[3])
    );
    hb_value_free(&dict);

    if (json_result < 0)
    {
        hb_error("preview params: json unpack failure: %s", error.text);
        return NULL;
    }

    image = hb_get_preview2(h, title_idx, preview_idx, &settings, deinterlace);
    if (image == NULL)
    {
        return NULL;
    }

    dict = json_pack_ex(&error, 0,
        "{s:o, s:o, s:o}",
            "Format",       hb_value_int(image->format),
            "Width",        hb_value_int(image->width),
            "Height",       hb_value_int(image->height));
    if (dict == NULL)
    {
        hb_error("hb_get_preview_json: pack failure: %s", error.text);
        return NULL;
    }

    hb_value_array_t * planes = hb_value_array_init();
    for (ii = 0; ii < 4; ii++)
    {
        int base64size = AV_BASE64_SIZE(image->plane[ii].size);
        if (image->plane[ii].size <= 0 || base64size <= 0)
            continue;

        char *plane_base64 = calloc(base64size, 1);
        av_base64_encode(plane_base64, base64size,
                         image->plane[ii].data, image->plane[ii].size);

        base64size = strlen(plane_base64);
        hb_dict_t *plane_dict;
        plane_dict = json_pack_ex(&error, 0,
            "{s:o, s:o, s:o, s:o, s:o, s:o}",
            "Width",        hb_value_int(image->plane[ii].width),
            "Height",       hb_value_int(image->plane[ii].height),
            "Stride",       hb_value_int(image->plane[ii].stride),
            "HeightStride", hb_value_int(image->plane[ii].height_stride),
            "Size",         hb_value_int(base64size),
            "Data",         hb_value_string(plane_base64)
        );
        if (plane_dict == NULL)
        {
            hb_error("plane_dict: json pack failure: %s", error.text);
            return NULL;
        }
        hb_value_array_append(planes, plane_dict);
    }
    hb_dict_set(dict, "Planes", planes);
    hb_image_close(&image);

    char *result = hb_value_get_json(dict);
    hb_value_free(&dict);

    return result;
}