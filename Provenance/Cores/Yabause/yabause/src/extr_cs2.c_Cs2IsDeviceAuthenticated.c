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
struct TYPE_3__ {int CR1; int /*<<< orphan*/  HIRQ; scalar_t__ CR4; scalar_t__ CR3; scalar_t__ CR2; } ;
struct TYPE_4__ {int status; TYPE_1__ reg; scalar_t__ satauth; scalar_t__ mpgauth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_HIRQ_CMOK ; 
 TYPE_2__* Cs2Area ; 

void Cs2IsDeviceAuthenticated(void) {
  Cs2Area->reg.CR1 = (Cs2Area->status << 8);
  if (Cs2Area->reg.CR2)
     Cs2Area->reg.CR2 = Cs2Area->mpgauth;
  else
     Cs2Area->reg.CR2 = Cs2Area->satauth;
  Cs2Area->reg.CR3 = 0;
  Cs2Area->reg.CR4 = 0;
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK;
}