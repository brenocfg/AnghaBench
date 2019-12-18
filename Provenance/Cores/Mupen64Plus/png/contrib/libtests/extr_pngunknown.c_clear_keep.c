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
struct TYPE_2__ {scalar_t__ keep; } ;

/* Variables and functions */
 int NINFO ; 
 TYPE_1__* chunk_info ; 

__attribute__((used)) static void
clear_keep(void)
{
   int i = NINFO;
   while (--i >= 0)
      chunk_info[i].keep = 0;
}