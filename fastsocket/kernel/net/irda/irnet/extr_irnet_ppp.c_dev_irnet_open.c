#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mtu; int hdrlen; int /*<<< orphan*/ * ops; struct irnet_socket* private; } ;
struct irnet_socket {int mru; unsigned int* xaccm; unsigned int raccm; int /*<<< orphan*/  event_index; TYPE_1__ chan; scalar_t__ ppp_open; struct file* file; } ;
struct inode {int dummy; } ;
struct file {struct irnet_socket* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  DABORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,struct file*) ; 
 int /*<<< orphan*/  DERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*,struct irnet_socket*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  FS_ERROR ; 
 int /*<<< orphan*/  FS_TRACE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PPP_HDRLEN ; 
 int TTP_MAX_HEADER ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int irda_irnet_create (struct irnet_socket*) ; 
 TYPE_2__ irnet_events ; 
 int /*<<< orphan*/  irnet_ppp_ops ; 
 int /*<<< orphan*/  kfree (struct irnet_socket*) ; 
 struct irnet_socket* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
dev_irnet_open(struct inode *	inode,
	       struct file *	file)
{
  struct irnet_socket *	ap;
  int			err;

  DENTER(FS_TRACE, "(file=0x%p)\n", file);

#ifdef SECURE_DEVIRNET
  /* This could (should?) be enforced by the permissions on /dev/irnet. */
  if(!capable(CAP_NET_ADMIN))
    return -EPERM;
#endif /* SECURE_DEVIRNET */

  /* Allocate a private structure for this IrNET instance */
  ap = kzalloc(sizeof(*ap), GFP_KERNEL);
  DABORT(ap == NULL, -ENOMEM, FS_ERROR, "Can't allocate struct irnet...\n");

  lock_kernel();
  /* initialize the irnet structure */
  ap->file = file;

  /* PPP channel setup */
  ap->ppp_open = 0;
  ap->chan.private = ap;
  ap->chan.ops = &irnet_ppp_ops;
  ap->chan.mtu = (2048 - TTP_MAX_HEADER - 2 - PPP_HDRLEN);
  ap->chan.hdrlen = 2 + TTP_MAX_HEADER;		/* for A/C + Max IrDA hdr */
  /* PPP parameters */
  ap->mru = (2048 - TTP_MAX_HEADER - 2 - PPP_HDRLEN);
  ap->xaccm[0] = ~0U;
  ap->xaccm[3] = 0x60000000U;
  ap->raccm = ~0U;

  /* Setup the IrDA part... */
  err = irda_irnet_create(ap);
  if(err)
    {
      DERROR(FS_ERROR, "Can't setup IrDA link...\n");
      kfree(ap);
      unlock_kernel();
      return err;
    }

  /* For the control channel */
  ap->event_index = irnet_events.index;	/* Cancel all past events */

  /* Put our stuff where we will be able to find it later */
  file->private_data = ap;

  DEXIT(FS_TRACE, " - ap=0x%p\n", ap);
  unlock_kernel();
  return 0;
}