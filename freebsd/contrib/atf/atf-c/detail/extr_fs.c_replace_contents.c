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
struct TYPE_3__ {int /*<<< orphan*/  m_data; } ;
typedef  TYPE_1__ atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  PRE (int) ; 
 int /*<<< orphan*/  atf_dynstr_append_fmt (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  atf_dynstr_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_dynstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static
void
replace_contents(atf_fs_path_t *p, const char *buf)
{
    atf_error_t err;

    PRE(atf_dynstr_length(&p->m_data) == strlen(buf));

    atf_dynstr_clear(&p->m_data);
    err = atf_dynstr_append_fmt(&p->m_data, "%s", buf);

    INV(!atf_is_error(err));
}