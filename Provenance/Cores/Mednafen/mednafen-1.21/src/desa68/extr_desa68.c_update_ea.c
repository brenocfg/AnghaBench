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
struct TYPE_2__ {int ea_src; int ea_dst; } ;

/* Variables and functions */
 TYPE_1__ d ; 

__attribute__((used)) static void update_ea(unsigned int v)
{
  v &= 0xFFFFFF;
  if (d.ea_src == -1) {
    d.ea_src = v;
  } else if (d.ea_dst == -1) {
    d.ea_dst = v;
  }
}