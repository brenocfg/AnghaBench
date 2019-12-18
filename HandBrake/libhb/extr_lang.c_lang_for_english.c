#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ eng_name; } ;
typedef  TYPE_1__ iso639_lang_t ;

/* Variables and functions */
 TYPE_1__ lang_any ; 
 scalar_t__ languages ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

iso639_lang_t * lang_for_english( const char * english )
{
    iso639_lang_t * lang;

    if (!strcmp(lang_any.eng_name, english))
    {
        return &lang_any;
    }
    for (lang = (iso639_lang_t*) languages; lang->eng_name; lang++)
    {
        if (!strcmp(lang->eng_name, english))
        {
            return lang;
        }
    }

    // Not found, return "Unknown"
    return (iso639_lang_t*) languages;
}