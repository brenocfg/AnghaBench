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
struct TYPE_3__ {char const* m_path; int m_type; } ;
typedef  TYPE_1__ unknown_type_error_data_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_error_new (char*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unknown_type_format ; 

__attribute__((used)) static
atf_error_t
unknown_type_error(const char *path, int type)
{
    atf_error_t err;
    unknown_type_error_data_t data;

    data.m_path = path;
    data.m_type = type;

    err = atf_error_new("unknown_type", &data, sizeof(data),
                        unknown_type_format);

    return err;
}