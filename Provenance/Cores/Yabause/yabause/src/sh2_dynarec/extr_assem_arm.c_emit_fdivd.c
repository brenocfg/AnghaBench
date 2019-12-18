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
 int /*<<< orphan*/  output_w32 (int) ; 

void emit_fdivd(int s1,int s2,int d)
{
  assem_debug("fdivd d%d,d%d,d%d\n",d,s1,s2);
  output_w32(0xee800b00|((d&7)<<12)|((s1&7)<<16)|(s2&7));
}