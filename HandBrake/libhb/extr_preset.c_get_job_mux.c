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
typedef  int /*<<< orphan*/  hb_dict_t ;
typedef  int /*<<< orphan*/  hb_container_t ;

/* Variables and functions */
 int HB_MUX_INVALID ; 
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 int /*<<< orphan*/  free (char*) ; 
 int hb_container_get_from_extension (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_container_get_from_format (int) ; 
 int hb_container_get_from_name (int /*<<< orphan*/ ) ; 
 void* hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_error (char*,char*) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_get_string (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string_xform (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_job_mux(hb_dict_t *job_dict)
{
    int mux;

    hb_dict_t *dest_dict = hb_dict_get(job_dict, "Destination");
    hb_value_t *mux_value = hb_dict_get(dest_dict, "Mux");
    if (hb_value_type(mux_value) == HB_VALUE_TYPE_STRING)
    {
        mux = hb_container_get_from_name(hb_value_get_string(mux_value));
        if (mux == 0)
            mux = hb_container_get_from_extension(
                                                hb_value_get_string(mux_value));
    }
    else
    {
        mux = hb_value_get_int(mux_value);
    }
    hb_container_t *container = hb_container_get_from_format(mux);
    if (container == NULL)
    {
        char *str = hb_value_get_string_xform(mux_value);
        hb_error("Invalid container (%s)", str);
        free(str);
        return HB_MUX_INVALID;
    }
    return mux;
}