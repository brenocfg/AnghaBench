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

/* Variables and functions */
 scalar_t__* c_file ; 
 int /*<<< orphan*/  dump_file (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__* export_file ; 
 scalar_t__* lderrout ; 
 scalar_t__* ldout ; 
 int /*<<< orphan*/  maybe_unlink (scalar_t__*) ; 
 scalar_t__* o_file ; 
 scalar_t__* output_file ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void
collect_exit (int status)
{
  if (c_file != 0 && c_file[0])
    maybe_unlink (c_file);

  if (o_file != 0 && o_file[0])
    maybe_unlink (o_file);

#ifdef COLLECT_EXPORT_LIST
  if (export_file != 0 && export_file[0])
    maybe_unlink (export_file);
#endif

  if (ldout != 0 && ldout[0])
    {
      dump_file (ldout, stdout);
      maybe_unlink (ldout);
    }

  if (lderrout != 0 && lderrout[0])
    {
      dump_file (lderrout, stderr);
      maybe_unlink (lderrout);
    }

  if (status != 0 && output_file != 0 && output_file[0])
    maybe_unlink (output_file);

  exit (status);
}