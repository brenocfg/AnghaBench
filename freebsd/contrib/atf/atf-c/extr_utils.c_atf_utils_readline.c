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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ch ;
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  atf_dynstr_append_fmt (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  atf_dynstr_fini (int /*<<< orphan*/ *) ; 
 char* atf_dynstr_fini_disown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_dynstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/ ) ; 
 int read (int const,char*,int) ; 

char *
atf_utils_readline(const int fd)
{
    char ch;
    ssize_t cnt;
    atf_dynstr_t temp;
    atf_error_t error;

    error = atf_dynstr_init(&temp);
    ATF_REQUIRE(!atf_is_error(error));

    while ((cnt = read(fd, &ch, sizeof(ch))) == sizeof(ch) &&
           ch != '\n') {
        error = atf_dynstr_append_fmt(&temp, "%c", ch);
        ATF_REQUIRE(!atf_is_error(error));
    }
    ATF_REQUIRE(cnt != -1);

    if (cnt == 0 && atf_dynstr_length(&temp) == 0) {
        atf_dynstr_fini(&temp);
        return NULL;
    } else
        return atf_dynstr_fini_disown(&temp);
}