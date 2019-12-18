#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int comment_count; int /*<<< orphan*/ * comment_refs; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ MXFTaggedValue ;
typedef  TYPE_2__ MXFPackage ;
typedef  int /*<<< orphan*/  MXFContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  TaggedValue ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* av_mallocz (int) ; 
 TYPE_1__* mxf_resolve_strong_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int mxf_parse_package_comments(MXFContext *mxf, AVDictionary **pm, MXFPackage *package)
{
    MXFTaggedValue *tag;
    int size, i;
    char *key = NULL;

    for (i = 0; i < package->comment_count; i++) {
        tag = mxf_resolve_strong_ref(mxf, &package->comment_refs[i], TaggedValue);
        if (!tag || !tag->name || !tag->value)
            continue;

        size = strlen(tag->name) + 8 + 1;
        key = av_mallocz(size);
        if (!key)
            return AVERROR(ENOMEM);

        snprintf(key, size, "comment_%s", tag->name);
        av_dict_set(pm, key, tag->value, AV_DICT_DONT_STRDUP_KEY);
    }
    return 0;
}