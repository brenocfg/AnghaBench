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
struct core_fns {scalar_t__ (* check_format ) (int /*<<< orphan*/ *) ;struct core_fns* next; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 struct core_fns* core_file_fns ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gdb_check_format (bfd *abfd)
{
  struct core_fns *cf;

  for (cf = core_file_fns; cf != NULL; cf = cf->next)
    {
      if (cf->check_format (abfd))
	{
	  return (1);
	}
    }
  return (0);
}