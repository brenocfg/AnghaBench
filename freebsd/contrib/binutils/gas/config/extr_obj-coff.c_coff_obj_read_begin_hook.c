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
typedef  int /*<<< orphan*/  SYMENT ;
typedef  int /*<<< orphan*/  AUXENT ;

/* Variables and functions */
 scalar_t__ AUXESZ ; 
 scalar_t__ SYMESZ ; 
 int /*<<< orphan*/  know (int) ; 
 int /*<<< orphan*/  tag_init () ; 

void
coff_obj_read_begin_hook (void)
{
  /* These had better be the same.  Usually 18 bytes.  */
  know (sizeof (SYMENT) == sizeof (AUXENT));
  know (SYMESZ == AUXESZ);
  tag_init ();
}