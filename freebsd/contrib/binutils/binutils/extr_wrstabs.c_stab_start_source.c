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
stab_start_source (void *p, const char *filename)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  /* FIXME: The symbol's value is supposed to be the text section
     address.  However, we would have to fill it in later, and gdb
     doesn't care, so we don't bother with it.  */

  info->lineno_filename = filename;

  return stab_write_symbol (info, N_SOL, 0, 0, filename);
}