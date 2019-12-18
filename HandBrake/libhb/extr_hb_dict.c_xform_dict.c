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
typedef  int hb_value_type_t ;
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  scalar_t__ hb_dict_iter_t ;

/* Variables and functions */
 scalar_t__ HB_DICT_ITER_DONE ; 
#define  HB_VALUE_TYPE_BOOL 132 
#define  HB_VALUE_TYPE_DOUBLE 131 
#define  HB_VALUE_TYPE_INT 130 
#define  HB_VALUE_TYPE_NULL 129 
#define  HB_VALUE_TYPE_STRING 128 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hb_dict_iter_init (int /*<<< orphan*/  const*) ; 
 char* hb_dict_iter_key (scalar_t__) ; 
 scalar_t__ hb_dict_iter_next (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/ * hb_dict_iter_value (scalar_t__) ; 
 char* hb_strdup_printf (char*,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_xform (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * json_null () ; 
 int /*<<< orphan*/ * json_string (char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static hb_value_t* xform_dict(const hb_value_t *dict, hb_value_type_t type)
{
    hb_value_t *first = NULL;
    hb_dict_iter_t iter = hb_dict_iter_init(dict);

    if (iter != HB_DICT_ITER_DONE)
        first = hb_dict_iter_value(iter);

    switch (type)
    {
        default:
        case HB_VALUE_TYPE_NULL:
        case HB_VALUE_TYPE_BOOL:
        case HB_VALUE_TYPE_INT:
        case HB_VALUE_TYPE_DOUBLE:
            return hb_value_xform(first, type);
        case HB_VALUE_TYPE_STRING:
        {
            char *r = strdup("");
            hb_dict_iter_t iter;
            for (iter  = hb_dict_iter_init(dict);
                 iter != HB_DICT_ITER_DONE;
                 iter  = hb_dict_iter_next(dict, iter))
            {
                const char *k = hb_dict_iter_key(iter);
                hb_value_t *v = hb_dict_iter_value(iter);
                hb_value_t *x = hb_value_xform(v, type);
                const char *s = hb_value_get_string(x);

                char *tmp = r;
                r = hb_strdup_printf("%s%s%s%s:",
                                     r,
                                     k,
                                     s  ? "=" : "",
                                     s  ? s   : "");
                free(tmp);
                hb_value_free(&x);
            }
            int len = strlen(r);
            hb_value_t *v;
            if (len > 0)
            {
                // Removing trailing ':'
                r[len - 1] = 0;
                v = json_string(r);
            }
            else
            {
                free(r);
                r = NULL;
                v = json_null();
            }
            free(r);
            return v;
        }
    }
}