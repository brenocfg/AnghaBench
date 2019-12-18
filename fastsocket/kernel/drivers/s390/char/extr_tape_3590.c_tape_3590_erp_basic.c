#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tape_request {int dummy; } ;
struct tape_device {int dummy; } ;
struct tape_3590_sense {int bra; } ;
struct irb {scalar_t__ ecw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SENSE_BRA_CONT 131 
#define  SENSE_BRA_DRE 130 
#define  SENSE_BRA_PER 129 
#define  SENSE_BRA_RE 128 
 int TAPE_IO_STOP ; 
 int tape_3590_erp_failed (struct tape_device*,struct tape_request*,struct irb*,int) ; 
 int tape_3590_erp_retry (struct tape_device*,struct tape_request*,struct irb*) ; 
 int tape_3590_erp_succeded (struct tape_device*,struct tape_request*) ; 

__attribute__((used)) static int
tape_3590_erp_basic(struct tape_device *device, struct tape_request *request,
		    struct irb *irb, int rc)
{
	struct tape_3590_sense *sense;

	sense = (struct tape_3590_sense *) irb->ecw;

	switch (sense->bra) {
	case SENSE_BRA_PER:
		return tape_3590_erp_failed(device, request, irb, rc);
	case SENSE_BRA_CONT:
		return tape_3590_erp_succeded(device, request);
	case SENSE_BRA_RE:
		return tape_3590_erp_retry(device, request, irb);
	case SENSE_BRA_DRE:
		return tape_3590_erp_failed(device, request, irb, rc);
	default:
		BUG();
		return TAPE_IO_STOP;
	}
}