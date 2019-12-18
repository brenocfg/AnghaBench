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
 int /*<<< orphan*/  DO_CLOSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action_file ; 
 int /*<<< orphan*/  code_file ; 
 int /*<<< orphan*/  code_file_name ; 
 int /*<<< orphan*/  defines_file ; 
 int /*<<< orphan*/  defines_file_name ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  externs_file ; 
 int /*<<< orphan*/  externs_file_name ; 
 scalar_t__ gflag ; 
 scalar_t__ got_intr ; 
 int /*<<< orphan*/  graph_file ; 
 int /*<<< orphan*/  graph_file_name ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  input_file ; 
 int /*<<< orphan*/  lalr_leaks () ; 
 int /*<<< orphan*/  lr0_leaks () ; 
 int /*<<< orphan*/  mkpar_leaks () ; 
 int /*<<< orphan*/  mstring_leaks () ; 
 scalar_t__ oflag ; 
 int /*<<< orphan*/  output_file ; 
 int /*<<< orphan*/  output_file_name ; 
 int /*<<< orphan*/  output_leaks () ; 
 int /*<<< orphan*/  reader_leaks () ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  text_file ; 
 int /*<<< orphan*/  union_file ; 
 int /*<<< orphan*/  verbose_file ; 
 int /*<<< orphan*/  verbose_file_name ; 
 scalar_t__ vflag ; 

void
done(int k)
{
    DO_CLOSE(input_file);
    DO_CLOSE(output_file);
    if (iflag)
	DO_CLOSE(externs_file);
    if (rflag)
	DO_CLOSE(code_file);

    DO_CLOSE(action_file);
    DO_CLOSE(defines_file);
    DO_CLOSE(graph_file);
    DO_CLOSE(text_file);
    DO_CLOSE(union_file);
    DO_CLOSE(verbose_file);

    if (got_intr)
	_exit(EXIT_FAILURE);

#ifdef NO_LEAKS
    if (rflag)
	DO_FREE(code_file_name);

    if (dflag)
	DO_FREE(defines_file_name);

    if (iflag)
	DO_FREE(externs_file_name);

    if (oflag)
	DO_FREE(output_file_name);

    if (vflag)
	DO_FREE(verbose_file_name);

    if (gflag)
	DO_FREE(graph_file_name);

    lr0_leaks();
    lalr_leaks();
    mkpar_leaks();
    mstring_leaks();
    output_leaks();
    reader_leaks();
#endif

    exit(k);
}