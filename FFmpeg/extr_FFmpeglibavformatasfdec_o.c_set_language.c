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
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LANG_ISO639_2_BIBL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ av_dict_set (int /*<<< orphan*/ **,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* ff_convert_lang_to (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void set_language(AVFormatContext *s, const char *rfc1766, AVDictionary **met)
{
    // language abbr should contain at least 2 chars
    if (rfc1766 && strlen(rfc1766) > 1) {
        const char primary_tag[3] = { rfc1766[0], rfc1766[1], '\0' }; // ignore country code if any
        const char *iso6392       = ff_convert_lang_to(primary_tag,
                                                       AV_LANG_ISO639_2_BIBL);
        if (iso6392)
            if (av_dict_set(met, "language", iso6392, 0) < 0)
                av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");
    }
}