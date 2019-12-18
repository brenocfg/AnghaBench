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
struct vio_driver_state {int dummy; } ;
struct vio_dring_register {int /*<<< orphan*/  num_cookies; int /*<<< orphan*/  options; int /*<<< orphan*/  descr_size; int /*<<< orphan*/  num_descr; scalar_t__ dring_ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int handshake_failure (struct vio_driver_state*) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_dreg_nack(struct vio_driver_state *vio,
			     struct vio_dring_register *pkt)
{
	viodbg(HS, "GOT DRING_REG NACK ident[%llx] "
	       "ndesc[%u] dsz[%u] opt[0x%x] ncookies[%u]\n",
	       (unsigned long long) pkt->dring_ident,
	       pkt->num_descr, pkt->descr_size, pkt->options,
	       pkt->num_cookies);

	return handshake_failure(vio);
}