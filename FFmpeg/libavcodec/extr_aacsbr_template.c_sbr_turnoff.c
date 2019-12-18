#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* kx; int /*<<< orphan*/  spectrum_params; TYPE_1__* data; scalar_t__* m; scalar_t__ ready_for_dequant; scalar_t__ start; } ;
struct TYPE_4__ {int* e_a; } ;
typedef  int /*<<< orphan*/  SpectrumParameters ;
typedef  TYPE_2__ SpectralBandReplication ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void sbr_turnoff(SpectralBandReplication *sbr) {
    sbr->start = 0;
    sbr->ready_for_dequant = 0;
    // Init defults used in pure upsampling mode
    sbr->kx[1] = 32; //Typo in spec, kx' inits to 32
    sbr->m[1] = 0;
    // Reset values for first SBR header
    sbr->data[0].e_a[1] = sbr->data[1].e_a[1] = -1;
    memset(&sbr->spectrum_params, -1, sizeof(SpectrumParameters));
}