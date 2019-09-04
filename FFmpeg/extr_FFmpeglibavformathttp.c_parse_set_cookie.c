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
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  WHITESPACES ; 
 scalar_t__ av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_strdup (char const*) ; 
 char* av_strtok (char*,char*,char**) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strspn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_set_cookie(const char *set_cookie, AVDictionary **dict)
{
    char *param, *next_param, *cstr, *back;

    if (!set_cookie[0])
        return 0;

    if (!(cstr = av_strdup(set_cookie)))
        return AVERROR(EINVAL);

    // strip any trailing whitespace
    back = &cstr[strlen(cstr)-1];
    while (strchr(WHITESPACES, *back)) {
        *back='\0';
        if (back == cstr)
            break;
        back--;
    }

    next_param = cstr;
    while ((param = av_strtok(next_param, ";", &next_param))) {
        char *name, *value;
        param += strspn(param, WHITESPACES);
        if ((name = av_strtok(param, "=", &value))) {
            if (av_dict_set(dict, name, value, 0) < 0) {
                av_free(cstr);
                return -1;
            }
        }
    }

    av_free(cstr);
    return 0;
}