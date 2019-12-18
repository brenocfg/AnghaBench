#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* buffer; } ;
typedef  TYPE_3__ cpp_reader ;
struct TYPE_7__ {TYPE_1__* file; } ;
struct TYPE_6__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cpp_find_file (TYPE_3__*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
_cpp_fake_include (cpp_reader *pfile, const char *fname)
{
  _cpp_find_file (pfile, fname, pfile->buffer->file->dir, true, 0);
}