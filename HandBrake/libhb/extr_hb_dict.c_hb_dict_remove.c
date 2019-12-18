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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ json_object_del (int /*<<< orphan*/ *,char const*) ; 
 char* makelower (char const*) ; 

int hb_dict_remove(hb_dict_t * dict, const char * key)
{
    int    result;

    // First try case sensitive lookup
    result = json_object_del(dict, key) == 0;
    if (!result)
    {
        // If not found, try case insensitive lookup
        char * lower = makelower(key);
        result = json_object_del(dict, lower) == 0;
        free(lower);
    }
    return result;
}