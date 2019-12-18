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
struct ldc_version {scalar_t__ major; scalar_t__ minor; } ;
struct ldc_packet {int dummy; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDC_INFO ; 
 int /*<<< orphan*/  LDC_VERS ; 
 struct ldc_version* find_by_major (scalar_t__) ; 
 struct ldc_packet* handshake_compose_ctrl (struct ldc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ldc_version*,int,unsigned long*) ; 
 int ldc_abort (struct ldc_channel*) ; 
 int send_tx_packet (struct ldc_channel*,struct ldc_packet*,unsigned long) ; 

__attribute__((used)) static int process_ver_nack(struct ldc_channel *lp, struct ldc_version *vp)
{
	struct ldc_version *vap;
	struct ldc_packet *p;
	unsigned long new_tail;

	if (vp->major == 0 && vp->minor == 0)
		return ldc_abort(lp);

	vap = find_by_major(vp->major);
	if (!vap)
		return ldc_abort(lp);

	p = handshake_compose_ctrl(lp, LDC_INFO, LDC_VERS,
					   vap, sizeof(*vap),
					   &new_tail);
	if (!p)
		return ldc_abort(lp);

	return send_tx_packet(lp, p, new_tail);
}