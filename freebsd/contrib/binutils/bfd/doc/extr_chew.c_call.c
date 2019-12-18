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
typedef  scalar_t__ stinst_type ;
typedef  int /*<<< orphan*/  dict_type ;

/* Variables and functions */
 int /*<<< orphan*/  exec (int /*<<< orphan*/ *) ; 
 scalar_t__* pc ; 

__attribute__((used)) static void
call ()
{
  stinst_type *oldpc = pc;
  dict_type *e;
  e = (dict_type *) (pc[1]);
  exec (e);
  pc = oldpc + 2;
}