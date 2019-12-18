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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int /*<<< orphan*/  free (char*) ; 
 int hb_audio_encoder_get_from_name (char const*) ; 
 int /*<<< orphan*/  hb_audio_encoder_get_short_name (int) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 char* hb_strdup_printf (char*,char const*) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_string (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static hb_value_t* get_audio_copy_mask(const hb_dict_t * preset, int *mask)
{
    int copy_mask = 0;
    hb_value_array_t *out_copy_mask, *in_copy_mask;

    if (mask != NULL)
        *mask = 0;
    in_copy_mask  = hb_dict_get(preset, "AudioCopyMask");
    out_copy_mask = hb_value_array_init();
    if (in_copy_mask != NULL)
    {
        int count, ii;
        count = hb_value_array_len(in_copy_mask);
        for (ii = 0; ii < count; ii++)
        {
            int codec;
            hb_value_t *value;
            value = hb_value_array_get(in_copy_mask, ii);
            if (hb_value_type(value) == HB_VALUE_TYPE_STRING)
            {
                char *tmp = NULL;
                const char * s = hb_value_get_string(value);
                // Only codecs that start with 'copy:' can be copied
                if (strncmp(s, "copy:", 5))
                {
                    s = tmp = hb_strdup_printf("copy:%s", s);
                }
                codec = hb_audio_encoder_get_from_name(s);
                if (codec == 0)
                {
                    hb_error("Invalid audio codec in autopassthru copy mask (%s)", s);
                    hb_error("Codec name is invalid or can not be copied");
                    free(tmp);
                    hb_value_free(&out_copy_mask);
                    return NULL;
                }
                free(tmp);
            }
            else
            {
                codec = hb_value_get_int(value);
            }
            hb_value_array_append(out_copy_mask, hb_value_string(
                hb_audio_encoder_get_short_name(codec)));
            copy_mask |= codec;
        }
    }
    if (mask != NULL)
        *mask = copy_mask;
    return out_copy_mask;
}