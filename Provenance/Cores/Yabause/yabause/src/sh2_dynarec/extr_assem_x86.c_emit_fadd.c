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
 int /*<<< orphan*/  assem_debug (char*,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 

void emit_fadd(int r)
{
  assem_debug("fadd st%d\n",r);
  output_byte(0xd8);
  output_byte(0xc0+r);
}