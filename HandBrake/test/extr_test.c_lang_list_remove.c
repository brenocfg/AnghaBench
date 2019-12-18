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
typedef  int /*<<< orphan*/  hb_value_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_remove (int /*<<< orphan*/ *,int) ; 
 char* hb_value_get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static void lang_list_remove(hb_value_array_t *list, const char *lang)
{
    int count = hb_value_array_len(list);
    int ii;
    for (ii = count - 1; ii >= 0; ii--)
    {
        const char *tmp = hb_value_get_string(hb_value_array_get(list, ii));
        if (!strncmp(lang, tmp, 4))
            hb_value_array_remove(list, ii);
    }
}