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
 int /*<<< orphan*/  FT_UNUSED (int) ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void
  abort_test( int  sig )
  {
    FT_UNUSED( sig );

    /* If a time-out happens, then kill the child */
    kill( child_pid, SIGFPE );
    write( 2, "Timeout... ", 11 );
  }