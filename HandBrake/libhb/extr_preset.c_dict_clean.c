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
typedef  scalar_t__ hb_value_type_t ;
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  scalar_t__ hb_dict_iter_t ;

/* Variables and functions */
 scalar_t__ HB_DICT_ITER_DONE ; 
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ hb_dict_iter_init (int /*<<< orphan*/ *) ; 
 char* hb_dict_iter_key (scalar_t__) ; 
 scalar_t__ hb_dict_iter_next (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * hb_dict_iter_value (scalar_t__) ; 
 int /*<<< orphan*/  hb_dict_remove (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*,char const*,char const*) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_value_get_bool (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_is_number (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_xform (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
dict_clean(hb_value_t *dict, hb_value_t *template)
{
    hb_value_t *tmp = hb_value_dup(dict);
    hb_dict_iter_t iter;
    const char *key;
    hb_value_t *val;
    hb_value_t *template_val;
    hb_value_type_t template_type, val_type;
    const char *preset_name = NULL;

    val = hb_dict_get(dict, "PresetName");
    if (val != NULL)
        preset_name = hb_value_get_string(val);

    // Remove keys that are not in the template and translate compatible
    // data types to the types used in the template.
    for (iter = hb_dict_iter_init(tmp);
         iter != HB_DICT_ITER_DONE;
         iter = hb_dict_iter_next(tmp, iter))
    {
        key = hb_dict_iter_key(iter);
        val = hb_dict_iter_value(iter);
        val_type = hb_value_type(val);

        template_val = hb_dict_get(template, key);
        template_type = hb_value_type(template_val);
        if (template_val == NULL)
        {
            // Unknown key.  These can be keys used privately by the
            // frontend.  So don't make noise about them.
            hb_dict_remove(dict, key);
        }
        else if (val_type != template_type)
        {
            if (val_type      == HB_VALUE_TYPE_DICT  ||
                val_type      == HB_VALUE_TYPE_ARRAY ||
                template_type == HB_VALUE_TYPE_DICT  ||
                template_type == HB_VALUE_TYPE_ARRAY)
            {
                hb_error("Preset %s: Incompatible value types for key %s. "
                         "Dropping.", preset_name, key);
                hb_dict_remove(dict, key);
            }
            else if (hb_value_is_number(val) &&
                     hb_value_is_number(template_val))
            {
                // Silently convert compatible numbers
                hb_value_t *v;
                v = hb_value_xform(val, template_type);
                hb_dict_set(dict, key, v);
            }
            else
            {
                hb_value_t *v;
                hb_error("Preset %s: Incorrect value type for key %s. "
                         "Converting.", preset_name, key);
                v = hb_value_xform(val, template_type);
                hb_dict_set(dict, key, v);
            }
        }
        else if (val_type      == HB_VALUE_TYPE_DICT &&
                 template_type == HB_VALUE_TYPE_DICT)
        {
            val = hb_dict_get(dict, key);
            dict_clean(val, template_val);
        }
        else if (val_type      == HB_VALUE_TYPE_ARRAY &&
                 template_type == HB_VALUE_TYPE_ARRAY &&
                 hb_value_array_len(template_val) > 0)
        {
            template_val = hb_value_array_get(template_val, 0);
            if (hb_value_type(template_val) == HB_VALUE_TYPE_DICT)
            {
                val = hb_dict_get(dict, key);
                int count = hb_value_array_len(val);
                int ii;
                for (ii = 0; ii < count; ii++)
                {
                    hb_value_t *array_val;
                    array_val = hb_value_array_get(val, ii);
                    if (hb_value_type(array_val) == HB_VALUE_TYPE_DICT)
                    {
                        dict_clean(array_val, template_val);
                    }
                }
            }
        }
    }
    hb_value_free(&tmp);

    if (!hb_value_get_bool(hb_dict_get(dict, "Folder")))
    {
        // Add key/value pairs that are in the template but not in the dict.
        for (iter = hb_dict_iter_init(template);
             iter != HB_DICT_ITER_DONE;
             iter = hb_dict_iter_next(template, iter))
        {
            key          = hb_dict_iter_key(iter);
            template_val = hb_dict_iter_value(iter);
            val          = hb_dict_get(dict, key);
            if (val == NULL)
            {
                hb_dict_set(dict, key, hb_value_dup(template_val));
            }
        }
    }
}