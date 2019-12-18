#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ style; } ;
struct TYPE_4__ {int unsigned_char; int warn_long_long; int warn_variadic_macros; scalar_t__ traditional; scalar_t__ directives_only; int /*<<< orphan*/  stdc_0_in_system_headers; int /*<<< orphan*/  preprocessed; TYPE_1__ deps; } ;

/* Variables and functions */
 scalar_t__ DEPS_NONE ; 
 scalar_t__ DINFO_LEVEL_NONE ; 
 int /*<<< orphan*/  STDC_0_IN_SYSTEM_HEADERS ; 
 TYPE_2__* cpp_opts ; 
 scalar_t__ debug_info_level ; 
 scalar_t__ deps_seen ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ flag_dump_includes ; 
 char flag_dump_macros ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int flag_no_line_commands ; 
 int flag_no_output ; 
 int /*<<< orphan*/  flag_signed_char ; 
 int flag_working_directory ; 
 scalar_t__ pedantic ; 
 scalar_t__ warn_long_long ; 
 scalar_t__ warn_traditional ; 
 scalar_t__ warn_unused_macros ; 
 scalar_t__ warn_variadic_macros ; 

__attribute__((used)) static void
sanitize_cpp_opts (void)
{
  /* If we don't know what style of dependencies to output, complain
     if any other dependency switches have been given.  */
  if (deps_seen && cpp_opts->deps.style == DEPS_NONE)
    error ("to generate dependencies you must specify either -M or -MM");

  /* -dM and dependencies suppress normal output; do it here so that
     the last -d[MDN] switch overrides earlier ones.  */
  if (flag_dump_macros == 'M')
    flag_no_output = 1;

  /* By default, -fdirectives-only implies -dD.  This allows subsequent phases
     to perform proper macro expansion.  */
  if (cpp_opts->directives_only && !cpp_opts->preprocessed && !flag_dump_macros)
    flag_dump_macros = 'D';

  /* Disable -dD, -dN and -dI if normal output is suppressed.  Allow
     -dM since at least glibc relies on -M -dM to work.  */
  /* Also, flag_no_output implies flag_no_line_commands, always.  */
  if (flag_no_output)
    {
      if (flag_dump_macros != 'M')
	flag_dump_macros = 0;
      flag_dump_includes = 0;
      flag_no_line_commands = 1;
    }

  cpp_opts->unsigned_char = !flag_signed_char;
  cpp_opts->stdc_0_in_system_headers = STDC_0_IN_SYSTEM_HEADERS;

  /* We want -Wno-long-long to override -pedantic -std=non-c99
     and/or -Wtraditional, whatever the ordering.  */
  cpp_opts->warn_long_long
    = warn_long_long && ((!flag_isoc99 && pedantic) || warn_traditional);

  /* Similarly with -Wno-variadic-macros.  No check for c99 here, since
     this also turns off warnings about GCCs extension.  */
  cpp_opts->warn_variadic_macros
    = warn_variadic_macros && (pedantic || warn_traditional);

  /* If we're generating preprocessor output, emit current directory
     if explicitly requested or if debugging information is enabled.
     ??? Maybe we should only do it for debugging formats that
     actually output the current directory?  */
  if (flag_working_directory == -1)
    flag_working_directory = (debug_info_level != DINFO_LEVEL_NONE);

  if (cpp_opts->directives_only)
    {
      if (warn_unused_macros)
	error ("-fdirectives-only is incompatible with -Wunused_macros");
      if (cpp_opts->traditional)
	error ("-fdirectives-only is incompatible with -traditional");
    }
}