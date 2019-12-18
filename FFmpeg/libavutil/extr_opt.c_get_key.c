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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  WHITESPACES ; 
 char* av_malloc (int) ; 
 scalar_t__ is_key_char (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strchr (char const*,char const) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_key(const char **ropts, const char *delim, char **rkey)
{
    const char *opts = *ropts;
    const char *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    while (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    if (!*opts || !strchr(delim, *opts))
        return AVERROR(EINVAL);
    opts++;
    if (!(*rkey = av_malloc(key_end - key_start + 1)))
        return AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    return 0;
}