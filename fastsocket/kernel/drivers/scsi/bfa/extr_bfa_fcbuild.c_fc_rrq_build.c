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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fc_rrq_s {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RXID_ANY ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct fc_rrq_s*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rrq_tmpl ; 

u16
fc_rrq_build(struct fchs_s *fchs, struct fc_rrq_s *rrq, u32 d_id, u32 s_id,
	     u16 ox_id, u16 rrq_oxid)
{
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	/*
	 * build rrq payload
	 */
	memcpy(rrq, &rrq_tmpl, sizeof(struct fc_rrq_s));
	rrq->s_id = (s_id);
	rrq->ox_id = cpu_to_be16(rrq_oxid);
	rrq->rx_id = FC_RXID_ANY;

	return sizeof(struct fc_rrq_s);
}