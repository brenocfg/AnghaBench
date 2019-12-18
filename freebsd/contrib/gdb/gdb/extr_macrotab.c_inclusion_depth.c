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
struct macro_source_file {struct macro_source_file* included_by; } ;

/* Variables and functions */

__attribute__((used)) static int
inclusion_depth (struct macro_source_file *file)
{
  int depth;

  for (depth = 0; file->included_by; depth++)
    file = file->included_by;

  return depth;
}