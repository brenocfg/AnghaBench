#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ttp_connect; int /*<<< orphan*/  max_sdu_size_rx; int /*<<< orphan*/  daddr; int /*<<< orphan*/  rsaddr; int /*<<< orphan*/  dtsap_sel; int /*<<< orphan*/  tsap; } ;
typedef  TYPE_1__ irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IRDA_SR_ERROR ; 
 int /*<<< orphan*/  IRDA_SR_TRACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int irnet_open_tsap (TYPE_1__*) ; 
 int irttp_connect_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
irnet_connect_tsap(irnet_socket *	self)
{
  int		err;

  DENTER(IRDA_SR_TRACE, "(self=0x%p)\n", self);

  /* Open a local TSAP (an IrTTP instance) */
  err = irnet_open_tsap(self);
  if(err != 0)
    {
      clear_bit(0, &self->ttp_connect);
      DERROR(IRDA_SR_ERROR, "connect aborted!\n");
      return(err);
    }

  /* Connect to remote device */
  err = irttp_connect_request(self->tsap, self->dtsap_sel,
			      self->rsaddr, self->daddr, NULL,
			      self->max_sdu_size_rx, NULL);
  if(err != 0)
    {
      clear_bit(0, &self->ttp_connect);
      DERROR(IRDA_SR_ERROR, "connect aborted!\n");
      return(err);
    }

  /* The above call is non-blocking.
   * After a while, the IrDA stack will either call us back in
   * irnet_connect_confirm() or irnet_disconnect_indication()
   * See you there ;-) */

  DEXIT(IRDA_SR_TRACE, "\n");
  return(err);
}