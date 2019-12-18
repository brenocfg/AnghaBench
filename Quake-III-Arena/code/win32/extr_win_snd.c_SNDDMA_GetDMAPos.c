#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int samples; } ;
struct TYPE_10__ {TYPE_1__* lpVtbl; } ;
struct TYPE_8__ {int sample; } ;
struct TYPE_9__ {TYPE_2__ u; int /*<<< orphan*/  wType; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* GetCurrentPosition ) (TYPE_4__*,int*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ MMTIME ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TIME_SAMPLES ; 
 TYPE_6__ dma ; 
 int /*<<< orphan*/  dsound_init ; 
 TYPE_4__* pDSBuf ; 
 int sample16 ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int*,int /*<<< orphan*/ *) ; 

int SNDDMA_GetDMAPos( void ) {
	MMTIME	mmtime;
	int		s;
	DWORD	dwWrite;

	if ( !dsound_init ) {
		return 0;
	}

	mmtime.wType = TIME_SAMPLES;
	pDSBuf->lpVtbl->GetCurrentPosition(pDSBuf, &mmtime.u.sample, &dwWrite);

	s = mmtime.u.sample;

	s >>= sample16;

	s &= (dma.samples-1);

	return s;
}