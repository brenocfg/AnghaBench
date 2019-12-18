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
struct bfi_ioc_ctrl_req_s {int /*<<< orphan*/  mh; } ;
struct bfa_ioc_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_IOC_H2I_DISABLE_REQ ; 
 int /*<<< orphan*/  BFI_MC_IOC ; 
 int /*<<< orphan*/  bfa_ioc_mbox_send (struct bfa_ioc_s*,struct bfi_ioc_ctrl_req_s*,int) ; 
 int /*<<< orphan*/  bfa_ioc_portid (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_send_disable(struct bfa_ioc_s *ioc)
{
	struct bfi_ioc_ctrl_req_s disable_req;

	bfi_h2i_set(disable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_DISABLE_REQ,
		    bfa_ioc_portid(ioc));
	bfa_ioc_mbox_send(ioc, &disable_req, sizeof(struct bfi_ioc_ctrl_req_s));
}