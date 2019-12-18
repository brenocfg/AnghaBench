#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int seen_once_only; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_6__ {int once_only; } ;
typedef  TYPE_2__ _cpp_file ;

/* Variables and functions */

void
_cpp_mark_file_once_only (cpp_reader *pfile, _cpp_file *file)
{
  pfile->seen_once_only = true;
  file->once_only = true;
}