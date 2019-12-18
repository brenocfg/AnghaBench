#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_7__ {int /*<<< orphan*/  file; int /*<<< orphan*/ * prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 int /*<<< orphan*/  _cpp_mark_file_once_only (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_eol (TYPE_2__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_pragma_once (cpp_reader *pfile)
{
  if (pfile->buffer->prev == NULL)
    cpp_error (pfile, CPP_DL_WARNING, "#pragma once in main file");

  check_eol (pfile);
  _cpp_mark_file_once_only (pfile, pfile->buffer->file);
}