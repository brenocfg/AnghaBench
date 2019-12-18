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
 int SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ ignore_SIGINT ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int signal_received ; 

__attribute__((used)) static void
catchsig (int s)
{
#if ! HAVE_SIGACTION
  signal (s, SIG_IGN);
#endif
  if (! (s == SIGINT && ignore_SIGINT))
    signal_received = s;
}