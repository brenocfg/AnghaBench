#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {TYPE_1__* lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* Unlock ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_4__ dma ; 
 int /*<<< orphan*/  locksize ; 
 TYPE_2__* pDSBuf ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SNDDMA_Submit( void ) {
    // unlock the dsound buffer
	if ( pDSBuf ) {
		pDSBuf->lpVtbl->Unlock(pDSBuf, dma.buffer, locksize, NULL, 0);
	}
}