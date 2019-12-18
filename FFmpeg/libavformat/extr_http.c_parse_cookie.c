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
struct tm {int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {char* key; scalar_t__ value; } ;
typedef  int /*<<< orphan*/  HTTPContext ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_KEY ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int av_gettime () ; 
 char* av_strndup (char const*,int) ; 
 int av_timegm (struct tm*) ; 
 scalar_t__ parse_set_cookie (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_set_cookie_expiry_time (scalar_t__,struct tm*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int parse_cookie(HTTPContext *s, const char *p, AVDictionary **cookies)
{
    AVDictionary *new_params = NULL;
    AVDictionaryEntry *e, *cookie_entry;
    char *eql, *name;

    // ensure the cookie is parsable
    if (parse_set_cookie(p, &new_params))
        return -1;

    // if there is no cookie value there is nothing to parse
    cookie_entry = av_dict_get(new_params, "", NULL, AV_DICT_IGNORE_SUFFIX);
    if (!cookie_entry || !cookie_entry->value) {
        av_dict_free(&new_params);
        return -1;
    }

    // ensure the cookie is not expired or older than an existing value
    if ((e = av_dict_get(new_params, "expires", NULL, 0)) && e->value) {
        struct tm new_tm = {0};
        if (!parse_set_cookie_expiry_time(e->value, &new_tm)) {
            AVDictionaryEntry *e2;

            // if the cookie has already expired ignore it
            if (av_timegm(&new_tm) < av_gettime() / 1000000) {
                av_dict_free(&new_params);
                return 0;
            }

            // only replace an older cookie with the same name
            e2 = av_dict_get(*cookies, cookie_entry->key, NULL, 0);
            if (e2 && e2->value) {
                AVDictionary *old_params = NULL;
                if (!parse_set_cookie(p, &old_params)) {
                    e2 = av_dict_get(old_params, "expires", NULL, 0);
                    if (e2 && e2->value) {
                        struct tm old_tm = {0};
                        if (!parse_set_cookie_expiry_time(e->value, &old_tm)) {
                            if (av_timegm(&new_tm) < av_timegm(&old_tm)) {
                                av_dict_free(&new_params);
                                av_dict_free(&old_params);
                                return -1;
                            }
                        }
                    }
                }
                av_dict_free(&old_params);
            }
        }
    }
    av_dict_free(&new_params);

    // duplicate the cookie name (dict will dupe the value)
    if (!(eql = strchr(p, '='))) return AVERROR(EINVAL);
    if (!(name = av_strndup(p, eql - p))) return AVERROR(ENOMEM);

    // add the cookie to the dictionary
    av_dict_set(cookies, name, eql, AV_DICT_DONT_STRDUP_KEY);

    return 0;
}