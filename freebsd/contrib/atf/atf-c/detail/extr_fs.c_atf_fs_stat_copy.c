#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  m_sb; int /*<<< orphan*/  m_type; } ;
typedef  TYPE_1__ atf_fs_stat_t ;

/* Variables and functions */

void
atf_fs_stat_copy(atf_fs_stat_t *dest, const atf_fs_stat_t *src)
{
    dest->m_type = src->m_type;
    dest->m_sb = src->m_sb;
}