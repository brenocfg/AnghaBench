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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_rotl(int t)
{
  assem_debug("rol %%%s\n",regname[t]);
  output_byte(0xD1);
  output_modrm(3,t,0);
}