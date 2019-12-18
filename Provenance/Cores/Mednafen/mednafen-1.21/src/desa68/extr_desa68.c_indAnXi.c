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
typedef  int u8 ;
typedef  int s32 ;
struct TYPE_2__ {int w; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  read_pc () ; 

__attribute__((used)) static s32 indAnXi()
{
  s32 v;
  read_pc();
  v  = (d.w&0x8000)? ('A'<<24) : ('D'<<24);
  v |= ('0'+((d.w>>12)&7)) << 16;
  v |= (u8)d.w<<8;
  v |= ((d.w&(1<<11))? 'L' : 'W');
  return v;
}