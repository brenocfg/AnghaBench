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
struct TYPE_3__ {char* m_path; scalar_t__ m_umask; int /*<<< orphan*/  m_type; } ;
typedef  TYPE_1__ invalid_umask_error_data_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* atf_error_data (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  atf_error_is (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,unsigned int) ; 
 char* stat_type_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
invalid_umask_format(const atf_error_t err, char *buf, size_t buflen)
{
    const invalid_umask_error_data_t *data;

    PRE(atf_error_is(err, "invalid_umask"));

    data = atf_error_data(err);
    snprintf(buf, buflen, "Could not create the temporary %s %s because "
             "it will not have enough access rights due to the current "
             "umask %05o", stat_type_to_string(data->m_type),
             data->m_path, (unsigned int)data->m_umask);
}