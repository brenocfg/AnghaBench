#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tm {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {char const* value; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cookie_dict; int /*<<< orphan*/  cookies; } ;
typedef  TYPE_1__ HTTPContext ;
typedef  TYPE_2__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_asprintf (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ av_strcasecmp (char const*,char const*) ; 
 char* av_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ av_strncasecmp (char const*,char const*,int) ; 
 char* av_strtok (char*,char*,char**) ; 
 int av_timegm (struct tm*) ; 
 scalar_t__ parse_cookie (TYPE_1__*,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ parse_set_cookie (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_set_cookie_expiry_time (char const*,struct tm*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int get_cookies(HTTPContext *s, char **cookies, const char *path,
                       const char *domain)
{
    // cookie strings will look like Set-Cookie header field values.  Multiple
    // Set-Cookie fields will result in multiple values delimited by a newline
    int ret = 0;
    char *cookie, *set_cookies, *next;

    // destroy any cookies in the dictionary.
    av_dict_free(&s->cookie_dict);

    if (!s->cookies)
        return 0;

    next = set_cookies = av_strdup(s->cookies);
    if (!next)
        return AVERROR(ENOMEM);

    *cookies = NULL;
    while ((cookie = av_strtok(next, "\n", &next)) && !ret) {
        AVDictionary *cookie_params = NULL;
        AVDictionaryEntry *cookie_entry, *e;

        // store the cookie in a dict in case it is updated in the response
        if (parse_cookie(s, cookie, &s->cookie_dict))
            av_log(s, AV_LOG_WARNING, "Unable to parse '%s'\n", cookie);

        // continue on to the next cookie if this one cannot be parsed
        if (parse_set_cookie(cookie, &cookie_params))
            goto skip_cookie;

        // if the cookie has no value, skip it
        cookie_entry = av_dict_get(cookie_params, "", NULL, AV_DICT_IGNORE_SUFFIX);
        if (!cookie_entry || !cookie_entry->value)
            goto skip_cookie;

        // if the cookie has expired, don't add it
        if ((e = av_dict_get(cookie_params, "expires", NULL, 0)) && e->value) {
            struct tm tm_buf = {0};
            if (!parse_set_cookie_expiry_time(e->value, &tm_buf)) {
                if (av_timegm(&tm_buf) < av_gettime() / 1000000)
                    goto skip_cookie;
            }
        }

        // if no domain in the cookie assume it appied to this request
        if ((e = av_dict_get(cookie_params, "domain", NULL, 0)) && e->value) {
            // find the offset comparison is on the min domain (b.com, not a.b.com)
            int domain_offset = strlen(domain) - strlen(e->value);
            if (domain_offset < 0)
                goto skip_cookie;

            // match the cookie domain
            if (av_strcasecmp(&domain[domain_offset], e->value))
                goto skip_cookie;
        }

        // ensure this cookie matches the path
        e = av_dict_get(cookie_params, "path", NULL, 0);
        if (!e || av_strncasecmp(path, e->value, strlen(e->value)))
            goto skip_cookie;

        // cookie parameters match, so copy the value
        if (!*cookies) {
            *cookies = av_asprintf("%s=%s", cookie_entry->key, cookie_entry->value);
        } else {
            char *tmp = *cookies;
            *cookies = av_asprintf("%s; %s=%s", tmp, cookie_entry->key, cookie_entry->value);
            av_free(tmp);
        }
        if (!*cookies)
            ret = AVERROR(ENOMEM);

    skip_cookie:
        av_dict_free(&cookie_params);
    }

    av_free(set_cookies);

    return ret;
}