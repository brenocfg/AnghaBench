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
struct TYPE_5__ {int disco_number; int disco_index; int /*<<< orphan*/  ttp_connect; int /*<<< orphan*/ * discoveries; int /*<<< orphan*/ * iriap; int /*<<< orphan*/  daddr; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DEV_ADDR_ANY ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DISCOVERY_DEFAULT_SLOTS ; 
 int /*<<< orphan*/  DRETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ENETUNREACH ; 
 int /*<<< orphan*/  IRDA_SR_INFO ; 
 int /*<<< orphan*/  IRDA_SR_TRACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iriap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * irlmp_get_discoveries (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int irnet_discover_next_daddr (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
irnet_discover_daddr_and_lsap_sel(irnet_socket *	self)
{
  int	ret;

  DENTER(IRDA_SR_TRACE, "(self=0x%p)\n", self);

  /* Ask lmp for the current discovery log */
  self->discoveries = irlmp_get_discoveries(&self->disco_number, self->mask,
					    DISCOVERY_DEFAULT_SLOTS);

  /* Check if the we got some results */
  if(self->discoveries == NULL)
    {
      self->disco_number = -1;
      clear_bit(0, &self->ttp_connect);
      DRETURN(-ENETUNREACH, IRDA_SR_INFO, "No Cachelog...\n");
    }
  DEBUG(IRDA_SR_INFO, "Got the log (0x%p), size is %d\n",
	self->discoveries, self->disco_number);

  /* Start with the first discovery */
  self->disco_index = -1;
  self->daddr = DEV_ADDR_ANY;

  /* This will fail if the log is empty - this is non-blocking */
  ret = irnet_discover_next_daddr(self);
  if(ret)
    {
      /* Close IAP */
      if(self->iriap)
	iriap_close(self->iriap);
      self->iriap = NULL;

      /* Cleanup our copy of the discovery log */
      kfree(self->discoveries);
      self->discoveries = NULL;

      clear_bit(0, &self->ttp_connect);
      DRETURN(-ENETUNREACH, IRDA_SR_INFO, "Cachelog empty...\n");
    }

  /* Follow me in irnet_discovervalue_confirm() */

  DEXIT(IRDA_SR_TRACE, "\n");
  return(0);
}