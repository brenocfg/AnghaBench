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
typedef  int /*<<< orphan*/  atf_fs_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static
bool
exists(const atf_fs_path_t *p)
{
    return access(atf_fs_path_cstring(p), F_OK) == 0;
}