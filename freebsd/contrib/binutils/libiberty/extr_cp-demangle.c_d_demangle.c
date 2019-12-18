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
struct d_growable_string {char* buf; scalar_t__ allocation_failure; } ;

/* Variables and functions */
 int d_demangle_callback (char const*,int,int /*<<< orphan*/ ,struct d_growable_string*) ; 
 int /*<<< orphan*/  d_growable_string_callback_adapter ; 
 int /*<<< orphan*/  d_growable_string_init (struct d_growable_string*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static char *
d_demangle (const char *mangled, int options, size_t *palc)
{
  struct d_growable_string dgs;
  int status;

  d_growable_string_init (&dgs, 0);

  status = d_demangle_callback (mangled, options,
                                d_growable_string_callback_adapter, &dgs);
  if (status == 0)
    {
      free (dgs.buf);
      *palc = 0;
      return NULL;
    }

  *palc = dgs.allocation_failure ? 1 : 0;
  return dgs.buf;
}