#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {int /*<<< orphan*/  st_dev; } ;
struct TYPE_5__ {TYPE_1__ m_sb; } ;
typedef  TYPE_2__ atf_fs_stat_t ;

/* Variables and functions */

dev_t
atf_fs_stat_get_device(const atf_fs_stat_t *st)
{
    return st->m_sb.st_dev;
}