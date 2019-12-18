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
 int /*<<< orphan*/  interrupt_query () ; 
 void ofunc (int) ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

__attribute__((used)) static void
nto_interrupt_twice (int signo)
{
  signal (signo, ofunc);
  interrupt_query ();
  signal (signo, nto_interrupt_twice);
}