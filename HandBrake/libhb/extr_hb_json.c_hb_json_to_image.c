#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_2__ json_error_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_9__ {TYPE_1__* plane; } ;
typedef  TYPE_3__ hb_image_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 int /*<<< orphan*/  av_base64_decode (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_image_init (int,int,int) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_json (char*) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int json_unpack_ex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  unpack_b (int*) ; 
 int /*<<< orphan*/  unpack_i (int*) ; 
 int /*<<< orphan*/  unpack_o (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  unpack_s (char const**) ; 

hb_image_t* hb_json_to_image(char *json_image)
{
    int json_result;
    json_error_t error;
    hb_dict_t * dict;
    int pix_fmt, width, height;
    dict = hb_value_json(json_image);
    json_result = json_unpack_ex(dict, &error, 0,
        "{"
        // Format, Width, Height
        "s:i, s:i, s:i,"
        "}",
        "Format",                   unpack_i(&pix_fmt),
        "Width",                    unpack_i(&width),
        "Height",                   unpack_b(&height)
    );
    if (json_result < 0)
    {
        hb_error("image: json unpack failure: %s", error.text);
        hb_value_free(&dict);
        return NULL;
    }

    hb_image_t *image = hb_image_init(pix_fmt, width, height);
    if (image == NULL)
    {
        hb_value_free(&dict);
        return NULL;
    }

    hb_value_array_t * planes = NULL;
    json_result = json_unpack_ex(dict, &error, 0,
                                 "{s:o}", "Planes", unpack_o(&planes));
    if (json_result < 0)
    {
        hb_error("image::planes: json unpack failure: %s", error.text);
        hb_value_free(&dict);
        return image;
    }
    if (hb_value_type(planes) == HB_VALUE_TYPE_ARRAY)
    {
        int ii, count;
        hb_dict_t *plane_dict;
        count = hb_value_array_len(planes);
        for (ii = 0; ii < count; ii++)
        {
            plane_dict = hb_value_array_get(planes, ii);
            const char *data = NULL;
            int size;
            json_result = json_unpack_ex(plane_dict, &error, 0,
                                         "{s:i, s:s}",
                                         "Size", unpack_i(&size),
                                         "Data", unpack_s(&data));
            if (json_result < 0)
            {
                hb_error("image::plane::data: json unpack failure: %s", error.text);
                hb_value_free(&dict);
                return image;
            }
            if (image->plane[ii].size > 0 && data != NULL)
            {
                av_base64_decode(image->plane[ii].data, data,
                                 image->plane[ii].size);
            }
        }
    }
    hb_value_free(&dict);

    return image;
}