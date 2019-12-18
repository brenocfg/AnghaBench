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
struct TYPE_3__ {int m_type; char* m_path; } ;
typedef  TYPE_1__ unknown_type_error_data_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* atf_error_data (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  atf_error_is (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,char*) ; 

__attribute__((used)) static
void
unknown_type_format(const atf_error_t err, char *buf, size_t buflen)
{
    const unknown_type_error_data_t *data;

    PRE(atf_error_is(err, "unknown_type"));

    data = atf_error_data(err);
    snprintf(buf, buflen, "Unknown file type %d of %s", data->m_type,
             data->m_path);
}