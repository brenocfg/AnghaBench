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
struct TYPE_2__ {int w; int opsz; } ;

/* Variables and functions */
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_Dcc () ; 
 int /*<<< orphan*/  desa_Scc () ; 
 int /*<<< orphan*/  desa_addq_subq () ; 

__attribute__((used)) static void desa_line5(void)
{
  if((d.w&0370)==0310) {
    desa_Dcc();
  } else if(d.opsz==3) {
    desa_Scc();
  } else {
    desa_addq_subq();
  }
}