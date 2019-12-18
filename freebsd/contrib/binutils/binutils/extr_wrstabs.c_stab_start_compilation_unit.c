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
struct stab_write_handle {char const* lineno_filename; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  N_SOL ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bfd_boolean
stab_start_compilation_unit (void *p, const char *filename)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  /* We would normally output an N_SO symbol here.  However, that
     would force us to reset all of our type information.  I think we
     will be better off just outputting an N_SOL symbol, and not
     worrying about splitting information between files.  */

  info->lineno_filename = filename;

  return stab_write_symbol (info, N_SOL, 0, 0, filename);
}