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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_rex (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_mov64(int rs,int rt)
{
  assem_debug("mov %%%s,%%%s\n",regname[rs],regname[rt]);
  output_rex(1,rs>>3,0,rt>>3);
  output_byte(0x89);
  output_modrm(3,rt&7,rs&7);
}