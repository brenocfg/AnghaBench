#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ daddr; char* rname; scalar_t__ rdaddr; scalar_t__ ppp_open; int /*<<< orphan*/  ttp_open; int /*<<< orphan*/  tsap; int /*<<< orphan*/  saddr; } ;
typedef  TYPE_1__ irnet_socket ;
struct TYPE_10__ {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 scalar_t__ DEV_ADDR_ANY ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  IRDA_SERV_INFO ; 
 int /*<<< orphan*/  IRDA_SERV_TRACE ; 
 scalar_t__ hashbin_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hashbin_get_first (int /*<<< orphan*/ ) ; 
 scalar_t__ hashbin_get_next (int /*<<< orphan*/ ) ; 
 int irnet_daddr_to_dname (TYPE_1__*) ; 
 TYPE_2__ irnet_server ; 
 scalar_t__ irttp_get_daddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irttp_get_saddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline irnet_socket *
irnet_find_socket(irnet_socket *	self)
{
  irnet_socket *	new = (irnet_socket *) NULL;
  int			err;

  DENTER(IRDA_SERV_TRACE, "(self=0x%p)\n", self);

  /* Get the addresses of the requester */
  self->daddr = irttp_get_daddr(self->tsap);
  self->saddr = irttp_get_saddr(self->tsap);

  /* Try to get the IrDA nickname of the requester */
  err = irnet_daddr_to_dname(self);

  /* Protect access to the instance list */
  spin_lock_bh(&irnet_server.spinlock);

  /* So now, try to get an socket having specifically
   * requested that nickname */
  if(err == 0)
    {
      new = (irnet_socket *) hashbin_find(irnet_server.list,
					  0, self->rname);
      if(new)
	DEBUG(IRDA_SERV_INFO, "Socket 0x%p matches rname ``%s''.\n",
	      new, new->rname);
    }

  /* If no name matches, try to find an socket by the destination address */
  /* It can be either the requested destination address (set via the
   * control channel), or the current destination address if the
   * socket is in the middle of a connection request */
  if(new == (irnet_socket *) NULL)
    {
      new = (irnet_socket *) hashbin_get_first(irnet_server.list);
      while(new !=(irnet_socket *) NULL)
	{
	  /* Does it have the same address ? */
	  if((new->rdaddr == self->daddr) || (new->daddr == self->daddr))
	    {
	      /* Yes !!! Get it.. */
	      DEBUG(IRDA_SERV_INFO, "Socket 0x%p matches daddr %#08x.\n",
		    new, self->daddr);
	      break;
	    }
	  new = (irnet_socket *) hashbin_get_next(irnet_server.list);
	}
    }

  /* If we don't have any socket, get the first unconnected socket */
  if(new == (irnet_socket *) NULL)
    {
      new = (irnet_socket *) hashbin_get_first(irnet_server.list);
      while(new !=(irnet_socket *) NULL)
	{
	  /* Is it available ? */
	  if(!(test_bit(0, &new->ttp_open)) && (new->rdaddr == DEV_ADDR_ANY) &&
	     (new->rname[0] == '\0') && (new->ppp_open))
	    {
	      /* Yes !!! Get it.. */
	      DEBUG(IRDA_SERV_INFO, "Socket 0x%p is free.\n",
		    new);
	      break;
	    }
	  new = (irnet_socket *) hashbin_get_next(irnet_server.list);
	}
    }

  /* Spin lock end */
  spin_unlock_bh(&irnet_server.spinlock);

  DEXIT(IRDA_SERV_TRACE, " - new = 0x%p\n", new);
  return new;
}