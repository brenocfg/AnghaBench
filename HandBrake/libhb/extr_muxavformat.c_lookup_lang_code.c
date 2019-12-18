#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* iso639_2b; char* iso639_2; } ;
typedef  TYPE_1__ iso639_lang_t ;

/* Variables and functions */
#define  HB_MUX_AV_MKV 130 
#define  HB_MUX_AV_MP4 129 
#define  HB_MUX_AV_WEBM 128 
 TYPE_1__* lang_for_code2 (char*) ; 

__attribute__((used)) static char* lookup_lang_code(int mux, char *iso639_2)
{
    iso639_lang_t   *lang;
    char *out = NULL;

    switch (mux)
    {
        case HB_MUX_AV_MP4:
            out = iso639_2;
            break;
        case HB_MUX_AV_MKV:
        case HB_MUX_AV_WEBM: // webm is a subset of mkv
            // MKV lang codes should be ISO-639-2B if it exists,
            // else ISO-639-2
            lang =  lang_for_code2( iso639_2 );
            out = lang->iso639_2b ? lang->iso639_2b : lang->iso639_2;
            break;
        default:
            break;
    }
    return out;
}