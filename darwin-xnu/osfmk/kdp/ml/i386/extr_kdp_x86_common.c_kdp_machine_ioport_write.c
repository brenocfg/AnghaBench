#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  kdp_x86_xcpu_func_t ;
struct TYPE_4__ {scalar_t__ address; scalar_t__ nbytes; } ;
typedef  TYPE_1__ kdp_writeioport_req_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int KDPERR_BADFLAVOR ; 
 int KDPERR_NO_ERROR ; 
 scalar_t__ KDP_CURRENT_LCPU ; 
 scalar_t__ cpu_number () ; 
 scalar_t__ kdp_x86_xcpu_invoke (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

int
kdp_machine_ioport_write(kdp_writeioport_req_t *rq, caddr_t data, uint16_t lcpu)
{
	uint16_t addr = rq->address;
	uint16_t size = rq->nbytes;

	if ((lcpu != KDP_CURRENT_LCPU) && (lcpu != cpu_number())) {
		return (int) kdp_x86_xcpu_invoke(lcpu, (kdp_x86_xcpu_func_t)kdp_machine_ioport_write, rq, data);
	}

	switch (size)
	{
	case 1:
		outb(addr, *((uint8_t *) data));
		break;
	case 2:
		outw(addr, *((uint16_t *) data));
		break;
	case 4:
		outl(addr, *((uint32_t *) data));
		break;
	default:
		return KDPERR_BADFLAVOR;
	}

	return KDPERR_NO_ERROR;
}