#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pu_mb_R; } ;
struct spu_state {TYPE_3__ prob; TYPE_2__* lscsa; } ;
struct spu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * slot; } ;
struct TYPE_5__ {TYPE_1__ ppu_mb; } ;

/* Variables and functions */

__attribute__((used)) static inline void setup_ppu_mb(struct spu_state *csa, struct spu *spu)
{
	/* Restore, Step 35:
	 *     Copy the CSA.PU_MB data into the LSCSA.
	 */
	csa->lscsa->ppu_mb.slot[0] = csa->prob.pu_mb_R;
}