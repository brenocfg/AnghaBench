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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_DICT_DONT_STRDUP_KEY ; 
 int AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int strlen (char const*) ; 
 char* unescape (char const*,int) ; 

__attribute__((used)) static int read_tag(const uint8_t *line, AVDictionary **m)
{
    uint8_t *key, *value;
    const uint8_t *p = line;

    /* find first not escaped '=' */
    while (1) {
        if (*p == '=')
            break;
        else if (*p == '\\')
            p++;

        if (*p++)
            continue;

        return 0;
    }

    if (!(key = unescape(line, p - line)))
        return AVERROR(ENOMEM);
    if (!(value = unescape(p + 1, strlen(p + 1)))) {
        av_free(key);
        return AVERROR(ENOMEM);
    }

    av_dict_set(m, key, value, AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);
    return 0;
}