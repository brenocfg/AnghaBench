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
struct TYPE_4__ {scalar_t__ iso639_2b; scalar_t__ iso639_2; scalar_t__ eng_name; } ;
typedef  TYPE_1__ iso639_lang_t ;

/* Variables and functions */
 TYPE_1__ lang_any ; 
 scalar_t__ languages ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 char tolower (char const) ; 

iso639_lang_t * lang_for_code2( const char *code )
{
    char code_string[4];
    iso639_lang_t * lang;

    code_string[0] = tolower( code[0] );
    code_string[1] = tolower( code[1] );
    code_string[2] = tolower( code[2] );
    code_string[3] = 0;

    if ((lang_any.iso639_2  && !strcmp(lang_any.iso639_2,  code_string)) ||
        (lang_any.iso639_2b && !strcmp(lang_any.iso639_2b, code_string)))
    {
        return &lang_any;
    }

    for( lang = (iso639_lang_t*) languages; lang->eng_name; lang++ )
    {
        if ((lang->iso639_2  && !strcmp(lang->iso639_2,  code_string)) ||
            (lang->iso639_2b && !strcmp(lang->iso639_2b, code_string)))
        {
            return lang;
        }
    }

    // Not found, return "Unknown"
    return (iso639_lang_t*) languages;
}