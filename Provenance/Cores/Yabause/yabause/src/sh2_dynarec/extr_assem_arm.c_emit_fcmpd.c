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
 int /*<<< orphan*/  output_w32 (int) ; 

void emit_fcmpd(int x,int y)
{
  assem_debug("fcmpd d6, d7\n");
  output_w32(0xeeb46b47);
}