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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  VCOS_LOG_LEVEL_T ;
typedef  int /*<<< orphan*/  VCOS_LOG_CAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_vlog_impl_func (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void vcos_vlog_impl(const VCOS_LOG_CAT_T *cat, VCOS_LOG_LEVEL_T _level, const char *fmt, va_list args)
{
   vcos_vlog_impl_func( cat, _level, fmt, args );
}