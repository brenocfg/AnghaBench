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
struct TYPE_10__ {scalar_t__ method; scalar_t__ mgmt_class; int /*<<< orphan*/  status; } ;
struct TYPE_11__ {TYPE_4__ mad_hdr; } ;
struct TYPE_12__ {TYPE_5__ mad; } ;
struct TYPE_7__ {int /*<<< orphan*/ * grh; TYPE_5__* mad; } ;
struct TYPE_8__ {TYPE_1__ recv_buf; int /*<<< orphan*/ * wc; } ;
struct TYPE_9__ {TYPE_2__ recv_wc; int /*<<< orphan*/  wc; } ;
struct ib_mad_private {TYPE_6__ mad; int /*<<< orphan*/  grh; TYPE_3__ header; } ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 int /*<<< orphan*/  IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD_ATTRIB ; 
 scalar_t__ IB_MGMT_METHOD_GET ; 
 scalar_t__ IB_MGMT_METHOD_GET_RESP ; 
 scalar_t__ IB_MGMT_METHOD_SET ; 
 int /*<<< orphan*/  IB_SMP_DIRECTION ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ib_mad_private*,struct ib_mad_private*,int) ; 

__attribute__((used)) static bool generate_unmatched_resp(struct ib_mad_private *recv,
				    struct ib_mad_private *response)
{
	if (recv->mad.mad.mad_hdr.method == IB_MGMT_METHOD_GET ||
	    recv->mad.mad.mad_hdr.method == IB_MGMT_METHOD_SET) {
		memcpy(response, recv, sizeof *response);
		response->header.recv_wc.wc = &response->header.wc;
		response->header.recv_wc.recv_buf.mad = &response->mad.mad;
		response->header.recv_wc.recv_buf.grh = &response->grh;
		response->mad.mad.mad_hdr.method = IB_MGMT_METHOD_GET_RESP;
		response->mad.mad.mad_hdr.status =
			cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD_ATTRIB);
		if (recv->mad.mad.mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)
			response->mad.mad.mad_hdr.status |= IB_SMP_DIRECTION;

		return true;
	} else {
		return false;
	}
}