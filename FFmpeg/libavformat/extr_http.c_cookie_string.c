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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cookie_string(AVDictionary *dict, char **cookies)
{
    AVDictionaryEntry *e = NULL;
    int len = 1;

    // determine how much memory is needed for the cookies string
    while (e = av_dict_get(dict, "", e, AV_DICT_IGNORE_SUFFIX))
        len += strlen(e->key) + strlen(e->value) + 1;

    // reallocate the cookies
    e = NULL;
    if (*cookies) av_free(*cookies);
    *cookies = av_malloc(len);
    if (!*cookies) return AVERROR(ENOMEM);
    *cookies[0] = '\0';

    // write out the cookies
    while (e = av_dict_get(dict, "", e, AV_DICT_IGNORE_SUFFIX))
        av_strlcatf(*cookies, len, "%s%s\n", e->key, e->value);

    return 0;
}