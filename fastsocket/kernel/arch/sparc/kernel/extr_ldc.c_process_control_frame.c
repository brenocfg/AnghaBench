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
struct ldc_packet {int ctrl; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
#define  LDC_RDX 131 
#define  LDC_RTR 130 
#define  LDC_RTS 129 
#define  LDC_VERS 128 
 int ldc_abort (struct ldc_channel*) ; 
 int process_rdx (struct ldc_channel*,struct ldc_packet*) ; 
 int process_rtr (struct ldc_channel*,struct ldc_packet*) ; 
 int process_rts (struct ldc_channel*,struct ldc_packet*) ; 
 int process_version (struct ldc_channel*,struct ldc_packet*) ; 

__attribute__((used)) static int process_control_frame(struct ldc_channel *lp,
				 struct ldc_packet *p)
{
	switch (p->ctrl) {
	case LDC_VERS:
		return process_version(lp, p);

	case LDC_RTS:
		return process_rts(lp, p);

	case LDC_RTR:
		return process_rtr(lp, p);

	case LDC_RDX:
		return process_rdx(lp, p);

	default:
		return ldc_abort(lp);
	}
}