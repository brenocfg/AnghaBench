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
struct TYPE_3__ {int CR1; int CR2; int HIRQ; } ;
struct TYPE_4__ {int getsectsize; int putsectsize; TYPE_1__ reg; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CDB_HIRQ_CMOK ; 
 int CDB_HIRQ_ESEL ; 
 TYPE_2__* Cs2Area ; 
 int /*<<< orphan*/  doCDReport (int /*<<< orphan*/ ) ; 

void Cs2SetSectorLength(void) {
  switch (Cs2Area->reg.CR1 & 0xFF) {
    case 0:
            Cs2Area->getsectsize = 2048;
            break;
    case 1:
            Cs2Area->getsectsize = 2336;
            break;
    case 2:
            Cs2Area->getsectsize = 2340;
            break;
    case 3:
            Cs2Area->getsectsize = 2352;
            break;
    default: break;
  }

  switch (Cs2Area->reg.CR2 >> 8) {
    case 0:
            Cs2Area->putsectsize = 2048;
            break;
    case 1:
            Cs2Area->putsectsize = 2336;
            break;
    case 2:
            Cs2Area->putsectsize = 2340;
            break;
    case 3:
            Cs2Area->putsectsize = 2352;
            break;
    default: break;
  }

  doCDReport(Cs2Area->status);
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK | CDB_HIRQ_ESEL;
}