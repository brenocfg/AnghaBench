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
typedef  int /*<<< orphan*/  hb_filter_param_t ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int GhbType ;

/* Variables and functions */
#define  GHB_BOOL 131 
#define  GHB_DOUBLE 130 
#define  GHB_INT 129 
#define  GHB_STRING 128 
 int /*<<< orphan*/ * ghb_int_value_new (int) ; 
 int /*<<< orphan*/ * ghb_string_value_new (char const*) ; 
 int /*<<< orphan*/ * hb_filter_param_get_presets (int) ; 
 int /*<<< orphan*/ * hb_filter_param_get_tunes (int) ; 
 int lookup_param_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 char* lookup_param_option (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static GhbValue *
filter_opt_get2(const char *name, const GhbValue *gval, GhbType type,
               int filter_id, int preset)
{
    GhbValue *result = NULL;
    hb_filter_param_t * param;

    if (preset)
    {
        param = hb_filter_param_get_presets(filter_id);
    }
    else
    {
        param = hb_filter_param_get_tunes(filter_id);
    }
    switch (type)
    {
        case GHB_DOUBLE:
        case GHB_BOOL:
        case GHB_INT:
        {
            int val;
            val = lookup_param_int(param, gval);
            return ghb_int_value_new(val);
        } break;
        case GHB_STRING:
        {
            const char *val;
            val = lookup_param_option(param, gval);
            return ghb_string_value_new(val);
        } break;
    }
    return result;
}