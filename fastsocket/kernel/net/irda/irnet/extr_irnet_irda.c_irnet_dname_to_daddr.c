#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irda_device_info {int /*<<< orphan*/  daddr; int /*<<< orphan*/  info; } ;
struct TYPE_4__ {int /*<<< orphan*/  rname; int /*<<< orphan*/  daddr; } ;
typedef  TYPE_1__ irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DISCOVERY_DEFAULT_SLOTS ; 
 int /*<<< orphan*/  DRETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ENETUNREACH ; 
 int /*<<< orphan*/  IRDA_SR_INFO ; 
 int /*<<< orphan*/  IRDA_SR_TRACE ; 
 int /*<<< orphan*/  NICKNAME_MAX_LEN ; 
 struct irda_device_info* irlmp_get_discoveries (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct irda_device_info*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
irnet_dname_to_daddr(irnet_socket *	self)
{
  struct irda_device_info *discoveries;	/* Copy of the discovery log */
  int	number;			/* Number of nodes in the log */
  int	i;

  DENTER(IRDA_SR_TRACE, "(self=0x%p)\n", self);

  /* Ask lmp for the current discovery log */
  discoveries = irlmp_get_discoveries(&number, 0xffff,
				      DISCOVERY_DEFAULT_SLOTS);
  /* Check if the we got some results */
  if(discoveries == NULL)
    DRETURN(-ENETUNREACH, IRDA_SR_INFO, "Cachelog empty...\n");

  /*
   * Now, check all discovered devices (if any), and connect
   * client only about the services that the client is
   * interested in...
   */
  for(i = 0; i < number; i++)
    {
      /* Does the name match ? */
      if(!strncmp(discoveries[i].info, self->rname, NICKNAME_MAX_LEN))
	{
	  /* Yes !!! Get it.. */
	  self->daddr = discoveries[i].daddr;
	  DEBUG(IRDA_SR_INFO, "discovered device ``%s'' at address 0x%08x.\n",
		self->rname, self->daddr);
	  kfree(discoveries);
	  DEXIT(IRDA_SR_TRACE, "\n");
	  return 0;
	}
    }
  /* No luck ! */
  DEBUG(IRDA_SR_INFO, "cannot discover device ``%s'' !!!\n", self->rname);
  kfree(discoveries);
  return(-EADDRNOTAVAIL);
}