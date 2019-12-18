#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* native_name; char* eng_name; char* iso639_2; } ;
typedef  TYPE_3__ iso639_lang_t ;
struct TYPE_7__ {int /*<<< orphan*/  iso639_2; int /*<<< orphan*/  simple; } ;
struct TYPE_8__ {TYPE_1__ lang; } ;
struct TYPE_10__ {TYPE_2__ config; } ;
typedef  TYPE_4__ hb_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void set_audio_description(hb_audio_t *audio, iso639_lang_t *lang)
{
    snprintf( audio->config.lang.simple,
              sizeof( audio->config.lang.simple ), "%s",
              strlen( lang->native_name ) ? lang->native_name : lang->eng_name );
    snprintf( audio->config.lang.iso639_2,
              sizeof( audio->config.lang.iso639_2 ), "%s", lang->iso639_2 );
}