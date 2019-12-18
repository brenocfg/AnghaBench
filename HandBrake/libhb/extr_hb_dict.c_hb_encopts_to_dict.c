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
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int HB_VCODEC_X264_MASK ; 
 int HB_VCODEC_X265_MASK ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_string (char*) ; 
 char* hb_x264_encopt_name (char const*) ; 
 char* hb_x265_encopt_name (char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 char* strdup (char const*) ; 

hb_dict_t * hb_encopts_to_dict(const char * encopts, int encoder)
{
    hb_dict_t * dict = NULL;

    if (encopts && *encopts)
    {
        char *cur_opt, *opts_start, *value;
        const char *name;
        dict = hb_dict_init();
        if( !dict )
            return NULL;
        cur_opt = opts_start = strdup(encopts);
        if (opts_start)
        {
            while (*cur_opt)
            {
                name = cur_opt;
                cur_opt += strcspn(cur_opt, ":");
                if (*cur_opt)
                {
                    *cur_opt = 0;
                    cur_opt++;
                }
                value = strchr(name, '=');
                if (value)
                {
                    *value = 0;
                    value++;
                }
                // x264 has multiple names for some options
                if (encoder & HB_VCODEC_X264_MASK)
                    name = hb_x264_encopt_name(name);
#if HB_PROJECT_FEATURE_X265
                // x265 has multiple names for some options
                if (encoder & HB_VCODEC_X265_MASK)
                    name = hb_x265_encopt_name(name);
#endif
                if (name != NULL)
                {
                    hb_dict_set(dict, name, hb_value_string(value));
                }
            }
        }
        free(opts_start);
    }
    return dict;
}