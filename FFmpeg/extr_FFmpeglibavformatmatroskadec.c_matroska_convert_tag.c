#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  key ;
struct TYPE_5__ {int nb_elem; TYPE_1__* elem; } ;
struct TYPE_4__ {char* lang; char* name; TYPE_2__ sub; int /*<<< orphan*/  string; scalar_t__ def; } ;
typedef  TYPE_1__ MatroskaTag ;
typedef  TYPE_2__ EbmlList ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ff_metadata_conv (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mkv_metadata_conv ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void matroska_convert_tag(AVFormatContext *s, EbmlList *list,
                                 AVDictionary **metadata, char *prefix)
{
    MatroskaTag *tags = list->elem;
    char key[1024];
    int i;

    for (i = 0; i < list->nb_elem; i++) {
        const char *lang = tags[i].lang &&
                           strcmp(tags[i].lang, "und") ? tags[i].lang : NULL;

        if (!tags[i].name) {
            av_log(s, AV_LOG_WARNING, "Skipping invalid tag with no TagName.\n");
            continue;
        }
        if (prefix)
            snprintf(key, sizeof(key), "%s/%s", prefix, tags[i].name);
        else
            av_strlcpy(key, tags[i].name, sizeof(key));
        if (tags[i].def || !lang) {
            av_dict_set(metadata, key, tags[i].string, 0);
            if (tags[i].sub.nb_elem)
                matroska_convert_tag(s, &tags[i].sub, metadata, key);
        }
        if (lang) {
            av_strlcat(key, "-", sizeof(key));
            av_strlcat(key, lang, sizeof(key));
            av_dict_set(metadata, key, tags[i].string, 0);
            if (tags[i].sub.nb_elem)
                matroska_convert_tag(s, &tags[i].sub, metadata, key);
        }
    }
    ff_metadata_conv(metadata, NULL, ff_mkv_metadata_conv);
}