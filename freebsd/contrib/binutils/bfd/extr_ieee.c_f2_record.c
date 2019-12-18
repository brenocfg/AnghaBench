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
 int /*<<< orphan*/  INT ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  OUT (int) ; 
 int /*<<< orphan*/  copy_till_end () ; 

__attribute__((used)) static void
f2_record (void)
{
  NEXT ();
  OUT (0xf2);
  INT;
  NEXT ();
  OUT (0xce);
  INT;
  copy_till_end ();
}