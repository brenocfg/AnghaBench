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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {char* value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  FFMIN (int,size_t) ; 
 int av_dict_count (int /*<<< orphan*/ *) ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static void dump_metadata(void *ctx, AVDictionary *m, const char *indent)
{
    if (m && !(av_dict_count(m) == 1 && av_dict_get(m, "language", NULL, 0))) {
        AVDictionaryEntry *tag = NULL;

        av_log(ctx, AV_LOG_INFO, "%sMetadata:\n", indent);
        while ((tag = av_dict_get(m, "", tag, AV_DICT_IGNORE_SUFFIX)))
            if (strcmp("language", tag->key)) {
                const char *p = tag->value;
                av_log(ctx, AV_LOG_INFO,
                       "%s  %-16s: ", indent, tag->key);
                while (*p) {
                    char tmp[256];
                    size_t len = strcspn(p, "\x8\xa\xb\xc\xd");
                    av_strlcpy(tmp, p, FFMIN(sizeof(tmp), len+1));
                    av_log(ctx, AV_LOG_INFO, "%s", tmp);
                    p += len;
                    if (*p == 0xd) av_log(ctx, AV_LOG_INFO, " ");
                    if (*p == 0xa) av_log(ctx, AV_LOG_INFO, "\n%s  %-16s: ", indent, "");
                    if (*p) p++;
                }
                av_log(ctx, AV_LOG_INFO, "\n");
            }
    }
}