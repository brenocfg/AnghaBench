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
struct TYPE_3__ {int CR1; int CR3; int /*<<< orphan*/  HIRQ; int /*<<< orphan*/  CR4; scalar_t__ CR2; } ;
struct TYPE_4__ {int status; TYPE_1__ reg; scalar_t__ blockfreespace; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_HIRQ_CMOK ; 
 TYPE_2__* Cs2Area ; 
 int /*<<< orphan*/  MAX_BLOCKS ; 
 int MAX_SELECTORS ; 

void Cs2GetBufferSize(void) {
  Cs2Area->reg.CR1 = Cs2Area->status << 8;
  Cs2Area->reg.CR2 = (u16)Cs2Area->blockfreespace;
  Cs2Area->reg.CR3 = MAX_SELECTORS << 8;
  Cs2Area->reg.CR4 = MAX_BLOCKS;
  Cs2Area->reg.HIRQ |= CDB_HIRQ_CMOK;
}