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
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_get_string (int /*<<< orphan*/ *,char**,char const,char const) ; 
 int av_dict_parse_string (int /*<<< orphan*/ **,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  print_dict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test_separators(const AVDictionary *m, const char pair, const char val)
{
    AVDictionary *dict = NULL;
    char pairs[] = {pair , '\0'};
    char vals[]  = {val, '\0'};

    char *buffer = NULL;
    int ret;

    av_dict_copy(&dict, m, 0);
    print_dict(dict);
    av_dict_get_string(dict, &buffer, val, pair);
    printf("%s\n", buffer);
    av_dict_free(&dict);
    ret = av_dict_parse_string(&dict, buffer, vals, pairs, 0);
    printf("ret %d\n", ret);
    av_freep(&buffer);
    print_dict(dict);
    av_dict_free(&dict);
}