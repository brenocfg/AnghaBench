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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * ghb_value_get_string (int /*<<< orphan*/  const*) ; 
 int lang_lookup_index (int /*<<< orphan*/  const*) ; 

int
ghb_lookup_lang(const GhbValue *glang)
{
    const gchar *str;

    str = ghb_value_get_string(glang);
    return lang_lookup_index(str);
}