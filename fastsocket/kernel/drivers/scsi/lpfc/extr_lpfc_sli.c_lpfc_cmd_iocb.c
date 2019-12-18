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
struct TYPE_3__ {int cmdidx; scalar_t__ cmdringaddr; } ;
struct TYPE_4__ {TYPE_1__ sli3; } ;
struct lpfc_sli_ring {TYPE_2__ sli; } ;
struct lpfc_hba {int iocb_cmd_size; } ;
typedef  int /*<<< orphan*/  IOCB_t ;

/* Variables and functions */

__attribute__((used)) static inline IOCB_t *
lpfc_cmd_iocb(struct lpfc_hba *phba, struct lpfc_sli_ring *pring)
{
	return (IOCB_t *) (((char *) pring->sli.sli3.cmdringaddr) +
			   pring->sli.sli3.cmdidx * phba->iocb_cmd_size);
}