#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  counter; scalar_t__ deps; } ;
typedef  TYPE_1__ cpp_reader ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  _cpp_save_file_entries (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpp_errno (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ deps_init () ; 
 scalar_t__ deps_save (scalar_t__,int /*<<< orphan*/ *) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

int
cpp_write_pch_state (cpp_reader *r, FILE *f)
{
  if (!r->deps)
    r->deps = deps_init ();

  if (deps_save (r->deps, f) != 0)
    {
      cpp_errno (r, CPP_DL_ERROR, "while writing precompiled header");
      return -1;
    }

  if (! _cpp_save_file_entries (r, f))
    {
      cpp_errno (r, CPP_DL_ERROR, "while writing precompiled header");
      return -1;
    }

  /* Save the next __COUNTER__ value.  When we include a precompiled header,
     we need to start at the offset we would have if the header had been
     included normally. */
  if (fwrite (&r->counter, sizeof (r->counter), 1, f) != 1)
    {
      cpp_errno (r, CPP_DL_ERROR, "while writing precompiled header");
      return -1;
    }

  return 0;
}