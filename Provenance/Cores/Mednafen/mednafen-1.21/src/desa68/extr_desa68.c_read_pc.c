#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int pc; int w; int (* mem_callb ) (unsigned int,int /*<<< orphan*/ ) ;unsigned int memmsk; int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int stub1 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_pc(void)
{
  unsigned int pc = d.pc;

/*
  d.w = (s8)d.mem[pc++&d.memmsk]<<8;
  d.w  += d.mem[pc++&d.memmsk];
*/

  d.w = d.mem_callb(pc & d.memmsk, d.private_data);
  pc += 2;

  d.pc = pc;
  return d.w;
}