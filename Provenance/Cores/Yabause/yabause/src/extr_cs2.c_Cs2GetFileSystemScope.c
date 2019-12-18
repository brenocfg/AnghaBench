#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int CR1; int CR3; int CR4; int HIRQ; scalar_t__ CR2; } ;
struct TYPE_4__ {int status; int numfiles; TYPE_1__ reg; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_EFLS ; 
 TYPE_2__* Cs2Area ; 

void Cs2GetFileSystemScope(void) {
  // may need to fix this
  Cs2Area->reg.CR1 = Cs2Area->status << 8;
  Cs2Area->reg.CR2 = (u16)(Cs2Area->numfiles - 2);
  Cs2Area->reg.CR3 = 0x0100;
  Cs2Area->reg.CR4 = 0x0002;

  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_EFLS;
}