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
struct irnet_socket {int /*<<< orphan*/  ppp_open; } ;
struct file {scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  struct irnet_socket irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DABORT (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,struct file*,struct irnet_socket*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  FS_ERROR ; 
 int /*<<< orphan*/  FS_TRACE ; 
 unsigned int POLLOUT ; 
 unsigned int POLLWRNORM ; 
 unsigned int irnet_ctrl_poll (struct irnet_socket*,struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
dev_irnet_poll(struct file *	file,
	       poll_table *	wait)
{
  irnet_socket *	ap = (struct irnet_socket *) file->private_data;
  unsigned int		mask;

  DENTER(FS_TRACE, "(file=0x%p, ap=0x%p)\n",
	 file, ap);

  mask = POLLOUT | POLLWRNORM;
  DABORT(ap == NULL, mask, FS_ERROR, "ap is NULL !!!\n");

  /* If we are connected to ppp_generic, let it handle the job */
  if(!ap->ppp_open)
    mask |= irnet_ctrl_poll(ap, file, wait);

  DEXIT(FS_TRACE, " - mask=0x%X\n", mask);
  return(mask);
}