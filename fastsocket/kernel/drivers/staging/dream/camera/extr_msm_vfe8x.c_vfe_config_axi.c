#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int** outFragments; } ;
struct TYPE_10__ {int** outFragments; } ;
struct TYPE_12__ {int fragmentCount; TYPE_5__ outputCbcr; TYPE_4__ outputY; } ;
struct TYPE_8__ {int** outFragments; } ;
struct TYPE_7__ {int** outFragments; } ;
struct TYPE_9__ {int fragmentCount; TYPE_2__ outputCbcr; TYPE_1__ outputY; } ;
struct vfe_cmd_axi_output_config {TYPE_6__ output2; TYPE_3__ output1; } ;
struct msm_pmem_region {int paddr; int y_off; int cbcr_off; } ;
struct axidata {int bufnum1; int bufnum2; struct msm_pmem_region* region; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,int,...) ; 
 int OUTPUT_1 ; 
 int OUTPUT_1_AND_2 ; 
 int OUTPUT_2 ; 

__attribute__((used)) static void vfe_config_axi(int mode,
	struct axidata *ad, struct vfe_cmd_axi_output_config *ao)
{
	struct msm_pmem_region *regptr;
	int i, j;
	uint32_t *p1, *p2;

	if (mode == OUTPUT_1 || mode == OUTPUT_1_AND_2) {
		regptr = ad->region;
		for (i = 0;
			i < ad->bufnum1; i++) {

			p1 = &(ao->output1.outputY.outFragments[i][0]);
			p2 = &(ao->output1.outputCbcr.outFragments[i][0]);

			for (j = 0;
				j < ao->output1.fragmentCount; j++) {

				*p1 = regptr->paddr + regptr->y_off;
				p1++;

				*p2 = regptr->paddr + regptr->cbcr_off;
				p2++;
			}
			regptr++;
		}
	} /* if OUTPUT1 or Both */

	if (mode == OUTPUT_2 || mode == OUTPUT_1_AND_2) {

		regptr = &(ad->region[ad->bufnum1]);
		CDBG("bufnum2 = %d\n", ad->bufnum2);

		for (i = 0;
			i < ad->bufnum2; i++) {

			p1 = &(ao->output2.outputY.outFragments[i][0]);
			p2 = &(ao->output2.outputCbcr.outFragments[i][0]);

		CDBG("config_axi: O2, phy = 0x%lx, y_off = %d, cbcr_off = %d\n",
			regptr->paddr, regptr->y_off, regptr->cbcr_off);

			for (j = 0;
				j < ao->output2.fragmentCount; j++) {

				*p1 = regptr->paddr + regptr->y_off;
				CDBG("vfe_config_axi: p1 = 0x%x\n", *p1);
				p1++;

				*p2 = regptr->paddr + regptr->cbcr_off;
				CDBG("vfe_config_axi: p2 = 0x%x\n", *p2);
				p2++;
			}
			regptr++;
		}
	}
}