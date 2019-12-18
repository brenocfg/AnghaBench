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
struct _cpp_file {int /*<<< orphan*/ * dir; } ;
typedef  int /*<<< orphan*/  cpp_dir ;

/* Variables and functions */

cpp_dir *
cpp_get_dir (struct _cpp_file *f)
{
  return f->dir;
}