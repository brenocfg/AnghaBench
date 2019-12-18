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
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_3__ {int m_type; char* m_path; int /*<<< orphan*/  m_umask; } ;
typedef  TYPE_1__ invalid_umask_error_data_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_error_new (char*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  invalid_umask_format ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
atf_error_t
invalid_umask_error(const atf_fs_path_t *path, const int type,
                    const mode_t failing_mask)
{
    atf_error_t err;
    invalid_umask_error_data_t data;

    data.m_type = type;

    strncpy(data.m_path, atf_fs_path_cstring(path), sizeof(data.m_path));
    data.m_path[sizeof(data.m_path) - 1] = '\0';

    data.m_umask = failing_mask;

    err = atf_error_new("invalid_umask", &data, sizeof(data),
                        invalid_umask_format);

    return err;
}