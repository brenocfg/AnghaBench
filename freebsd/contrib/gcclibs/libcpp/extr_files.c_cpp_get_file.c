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
struct TYPE_3__ {int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ cpp_buffer ;
typedef  int /*<<< orphan*/  _cpp_file ;

/* Variables and functions */

_cpp_file *
cpp_get_file (cpp_buffer *b)
{
  return b->file;
}