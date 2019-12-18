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
struct irnet_socket {int /*<<< orphan*/  chan; scalar_t__ ppp_open; } ;
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
typedef  struct irnet_socket irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DABORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,struct file*,struct irnet_socket*) ; 
 int /*<<< orphan*/  DERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FS_ERROR ; 
 int /*<<< orphan*/  FS_TRACE ; 
 int /*<<< orphan*/  irda_irnet_destroy (struct irnet_socket*) ; 
 int /*<<< orphan*/  kfree (struct irnet_socket*) ; 
 int /*<<< orphan*/  ppp_unregister_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dev_irnet_close(struct inode *	inode,
		struct file *	file)
{
  irnet_socket *	ap = (struct irnet_socket *) file->private_data;

  DENTER(FS_TRACE, "(file=0x%p, ap=0x%p)\n",
	 file, ap);
  DABORT(ap == NULL, 0, FS_ERROR, "ap is NULL !!!\n");

  /* Detach ourselves */
  file->private_data = NULL;

  /* Close IrDA stuff */
  irda_irnet_destroy(ap);

  /* Disconnect from the generic PPP layer if not already done */
  if(ap->ppp_open)
    {
      DERROR(FS_ERROR, "Channel still registered - deregistering !\n");
      ap->ppp_open = 0;
      ppp_unregister_channel(&ap->chan);
    }

  kfree(ap);

  DEXIT(FS_TRACE, "\n");
  return 0;
}