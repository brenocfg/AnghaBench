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
 int POPT_EN_FM ; 
 int PicoOpt ; 
 int emustatus ; 
 int ym2612_write_local (unsigned int,unsigned char,int) ; 

__attribute__((used)) static void z80_md_ym2612_write(unsigned int a, unsigned char data)
{
  if (PicoOpt & POPT_EN_FM)
    emustatus |= ym2612_write_local(a, data, 1) & 1;
}