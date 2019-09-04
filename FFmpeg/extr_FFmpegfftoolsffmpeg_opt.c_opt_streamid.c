#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  idx_str ;
struct TYPE_2__ {void** streamid_map; int /*<<< orphan*/  nb_streamid_map; } ;
typedef  TYPE_1__ OptionsContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ MAX_STREAMS ; 
 int /*<<< orphan*/  OPT_INT ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 void** grow_array (void**,int,int /*<<< orphan*/ *,int) ; 
 void* parse_number_or_die (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int opt_streamid(void *optctx, const char *opt, const char *arg)
{
    OptionsContext *o = optctx;
    int idx;
    char *p;
    char idx_str[16];

    av_strlcpy(idx_str, arg, sizeof(idx_str));
    p = strchr(idx_str, ':');
    if (!p) {
        av_log(NULL, AV_LOG_FATAL,
               "Invalid value '%s' for option '%s', required syntax is 'index:value'\n",
               arg, opt);
        exit_program(1);
    }
    *p++ = '\0';
    idx = parse_number_or_die(opt, idx_str, OPT_INT, 0, MAX_STREAMS-1);
    o->streamid_map = grow_array(o->streamid_map, sizeof(*o->streamid_map), &o->nb_streamid_map, idx+1);
    o->streamid_map[idx] = parse_number_or_die(opt, p, OPT_INT, 0, INT_MAX);
    return 0;
}