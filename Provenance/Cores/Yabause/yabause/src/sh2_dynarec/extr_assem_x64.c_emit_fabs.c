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
 int /*<<< orphan*/  assem_debug (char*) ; 
 int /*<<< orphan*/  output_byte (int) ; 

void emit_fabs()
{
  assem_debug("fabs\n");
  output_byte(0xd9);
  output_byte(0xe1);
}