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
typedef  int /*<<< orphan*/  u64 ;
struct vio_driver_state {int dr_state; int /*<<< orphan*/ * desc_buf; struct vio_dring_state* drings; } ;
struct vio_dring_state {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t VIO_DRIVER_RX_RING ; 
 int VIO_DR_STATE_RXREG ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vio_dring_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void flush_rx_dring(struct vio_driver_state *vio)
{
	struct vio_dring_state *dr;
	u64 ident;

	BUG_ON(!(vio->dr_state & VIO_DR_STATE_RXREG));

	dr = &vio->drings[VIO_DRIVER_RX_RING];
	ident = dr->ident;

	BUG_ON(!vio->desc_buf);
	kfree(vio->desc_buf);
	vio->desc_buf = NULL;

	memset(dr, 0, sizeof(*dr));
	dr->ident = ident;
}