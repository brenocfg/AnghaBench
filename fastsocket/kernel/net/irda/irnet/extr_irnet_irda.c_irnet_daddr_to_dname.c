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
struct irda_device_info {scalar_t__ daddr; int /*<<< orphan*/  info; } ;
struct TYPE_4__ {scalar_t__ daddr; char* rname; } ;
typedef  TYPE_1__ irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DISCOVERY_DEFAULT_SLOTS ; 
 int /*<<< orphan*/  DRETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ENETUNREACH ; 
 int /*<<< orphan*/  IRDA_SERV_INFO ; 
 int /*<<< orphan*/  IRDA_SERV_TRACE ; 
 struct irda_device_info* irlmp_get_discoveries (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct irda_device_info*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
irnet_daddr_to_dname(irnet_socket *	self)
{
  struct irda_device_info *discoveries;	/* Copy of the discovery log */
  int	number;			/* Number of nodes in the log */
  int	i;

  DENTER(IRDA_SERV_TRACE, "(self=0x%p)\n", self);

  /* Ask lmp for the current discovery log */
  discoveries = irlmp_get_discoveries(&number, 0xffff,
				      DISCOVERY_DEFAULT_SLOTS);
  /* Check if the we got some results */
  if (discoveries == NULL)
    DRETURN(-ENETUNREACH, IRDA_SERV_INFO, "Cachelog empty...\n");

  /* Now, check all discovered devices (if any) */
  for(i = 0; i < number; i++)
    {
      /* Does the name match ? */
      if(discoveries[i].daddr == self->daddr)
	{
	  /* Yes !!! Get it.. */
	  strlcpy(self->rname, discoveries[i].info, sizeof(self->rname));
	  self->rname[sizeof(self->rname) - 1] = '\0';
	  DEBUG(IRDA_SERV_INFO, "Device 0x%08x is in fact ``%s''.\n",
		self->daddr, self->rname);
	  kfree(discoveries);
	  DEXIT(IRDA_SERV_TRACE, "\n");
	  return 0;
	}
    }
  /* No luck ! */
  DEXIT(IRDA_SERV_INFO, ": cannot discover device 0x%08x !!!\n", self->daddr);
  kfree(discoveries);
  return(-EADDRNOTAVAIL);
}