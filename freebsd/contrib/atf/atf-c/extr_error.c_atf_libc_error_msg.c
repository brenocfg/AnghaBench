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
struct atf_libc_error_data {char const* m_what; } ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 struct atf_libc_error_data* atf_error_data (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  atf_error_is (int /*<<< orphan*/  const,char*) ; 

const char *
atf_libc_error_msg(const atf_error_t err)
{
    const struct atf_libc_error_data *data;

    PRE(atf_error_is(err, "libc"));

    data = atf_error_data(err);

    return data->m_what;
}