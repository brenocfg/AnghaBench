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
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__* c_file ; 
 scalar_t__* export_file ; 
 scalar_t__* lderrout ; 
 scalar_t__* ldout ; 
 int /*<<< orphan*/  maybe_unlink (scalar_t__*) ; 
 scalar_t__* o_file ; 
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handler (int signo)
{
  if (c_file != 0 && c_file[0])
    maybe_unlink (c_file);

  if (o_file != 0 && o_file[0])
    maybe_unlink (o_file);

  if (ldout != 0 && ldout[0])
    maybe_unlink (ldout);

  if (lderrout != 0 && lderrout[0])
    maybe_unlink (lderrout);

#ifdef COLLECT_EXPORT_LIST
  if (export_file != 0 && export_file[0])
    maybe_unlink (export_file);
#endif

  signal (signo, SIG_DFL);
  raise (signo);
}