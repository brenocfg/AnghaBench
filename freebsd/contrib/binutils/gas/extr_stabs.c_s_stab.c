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
 int /*<<< orphan*/  STAB_SECTION_NAME ; 
 int /*<<< orphan*/  STAB_STRING_SECTION_NAME ; 
 int /*<<< orphan*/  s_stab_generic (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
s_stab (int what)
{
  s_stab_generic (what, STAB_SECTION_NAME, STAB_STRING_SECTION_NAME);
}