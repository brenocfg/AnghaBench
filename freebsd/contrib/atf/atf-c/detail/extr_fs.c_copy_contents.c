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
 int /*<<< orphan*/  atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_dynstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
atf_error_t
copy_contents(const atf_fs_path_t *p, char **buf)
{
    atf_error_t err;
    char *str;

    str = (char *)malloc(atf_dynstr_length(&p->m_data) + 1);
    if (str == NULL)
        err = atf_no_memory_error();
    else {
        strcpy(str, atf_dynstr_cstring(&p->m_data));
        *buf = str;
        err = atf_no_error();
    }

    return err;
}