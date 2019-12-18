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
typedef  int s32 ;
struct TYPE_2__ {int pc; int w; int memmsk; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  read_pc () ; 

__attribute__((used)) static s32 relPC(void)
{
  read_pc();
  return (d.pc + d.w - 2) & d.memmsk;
}