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
 int /*<<< orphan*/  assem_debug (char*,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 

void emit_ftosizs(int s,int d)
{
  assem_debug("ftosizs s%d,s%d\n",d,s);
  output_w32(0xeebd0ac0|((d&14)<<11)|((d&1)<<22)|((s&14)>>1)|((s&1)<<5));
}