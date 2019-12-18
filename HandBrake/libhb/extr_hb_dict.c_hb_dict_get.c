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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/  const*,char const*) ; 
 char* makelower (char const*) ; 

hb_value_t * hb_dict_get(const hb_dict_t * dict, const char * key)
{
    hb_value_t * result;

    // First try case sensitive lookup
    result = json_object_get(dict, key);
    if (result == NULL)
    {
        // If not found, try case insensitive lookup
        char * lower = makelower(key);
        result = json_object_get(dict, lower);
        free(lower);
    }
    return result;
}