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
typedef  int /*<<< orphan*/  atf_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_CHECK_STREQ (char const*,char const*) ; 
 int /*<<< orphan*/  CE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_size (char const**) ; 
 int /*<<< orphan*/  atf_list_fini (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_list_index_c (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  atf_list_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_text_split (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static
void
check_split(const char *str, const char *delim, const char *words[])
{
    atf_list_t list;
    const char **word;
    size_t i;

    printf("Splitting '%s' with delimiter '%s'\n", str, delim);
    CE(atf_text_split(str, delim, &list));

    printf("Expecting %zd words\n", array_size(words));
    ATF_CHECK_EQ(atf_list_size(&list), array_size(words));

    for (word = words, i = 0; *word != NULL; word++, i++) {
        printf("Word at position %zd should be '%s'\n", i, words[i]);
        ATF_CHECK_STREQ((const char *)atf_list_index_c(&list, i), words[i]);
    }

    atf_list_fini(&list);
}