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
struct TYPE_3__ {int /*<<< orphan*/  opts; } ;
typedef  TYPE_1__ cpp_reader ;
typedef  int /*<<< orphan*/  cpp_options ;

/* Variables and functions */

cpp_options *
cpp_get_options (cpp_reader *pfile)
{
  return &pfile->opts;
}