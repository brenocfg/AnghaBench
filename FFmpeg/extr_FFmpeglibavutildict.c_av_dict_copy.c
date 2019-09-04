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
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/  const*,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int av_dict_set (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int av_dict_copy(AVDictionary **dst, const AVDictionary *src, int flags)
{
    AVDictionaryEntry *t = NULL;

    while ((t = av_dict_get(src, "", t, AV_DICT_IGNORE_SUFFIX))) {
        int ret = av_dict_set(dst, t->key, t->value, flags);
        if (ret < 0)
            return ret;
    }

    return 0;
}