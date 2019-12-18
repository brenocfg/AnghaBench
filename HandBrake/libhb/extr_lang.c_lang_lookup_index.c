#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ native_name; scalar_t__ eng_name; scalar_t__ iso639_2b; scalar_t__ iso639_2; scalar_t__ iso639; scalar_t__ iso639_1; } ;
typedef  TYPE_1__ iso639_lang_t ;
struct TYPE_5__ {scalar_t__ native_name; scalar_t__ eng_name; scalar_t__ iso639_2b; scalar_t__ iso639_2; scalar_t__ iso639; scalar_t__ iso639_1; } ;

/* Variables and functions */
 TYPE_3__ lang_any ; 
 TYPE_1__* languages ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char const*) ; 

const int lang_lookup_index( const char * str )
{
    int             ii = 0;
    const iso639_lang_t * lang;

    // We use fake lang_any iso639 to designate a match for "Any" language
    if ((lang_any.iso639_1    && !strcasecmp(lang_any.iso639_1,    str)) ||
        (lang_any.iso639      && !strcasecmp(lang_any.iso639,      str)) ||
        (lang_any.iso639_2    && !strcasecmp(lang_any.iso639_2,    str)) ||
        (lang_any.iso639_2b   && !strcasecmp(lang_any.iso639_2b,   str)) ||
        (lang_any.eng_name    && !strcasecmp(lang_any.eng_name,    str)) ||
        (lang_any.native_name && !strcasecmp(lang_any.native_name, str)))
    {
        return -1;
    }

    for (ii = 0; languages[ii].eng_name; ii++)
    {
        lang = &languages[ii];
        if ((lang->iso639_1    && !strcasecmp(lang->iso639_1,    str)) ||
            (lang->iso639      && !strcasecmp(lang->iso639,      str)) ||
            (lang->iso639_2    && !strcasecmp(lang->iso639_2,    str)) ||
            (lang->iso639_2b   && !strcasecmp(lang->iso639_2b,   str)) ||
            (lang->eng_name    && !strcasecmp(lang->eng_name,    str)) ||
            (lang->native_name && !strcasecmp(lang->native_name, str)))
        {
            return ii;
        }
    }

    return -1;
}