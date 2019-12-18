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
 int /*<<< orphan*/  assem_debug (char*,int,int,int) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 

void emit_call(int a)
{
  assem_debug("call %x (%x+%x)\n",a,(int)out+5,a-(int)out-5);
  output_byte(0xe8);
  output_w32(a-(int)out-4);
}