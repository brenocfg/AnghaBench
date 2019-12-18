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
struct fib {int dummy; } ;
struct aac_dev {int dummy; } ;
struct aac_close {void* cid; void* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ContainerCommand ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FsaNormal ; 
 int VM_CloseAll ; 
 struct fib* aac_fib_alloc (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ fib_data (struct fib*) ; 

int aac_send_shutdown(struct aac_dev * dev)
{
	struct fib * fibctx;
	struct aac_close *cmd;
	int status;

	fibctx = aac_fib_alloc(dev);
	if (!fibctx)
		return -ENOMEM;
	aac_fib_init(fibctx);

	cmd = (struct aac_close *) fib_data(fibctx);

	cmd->command = cpu_to_le32(VM_CloseAll);
	cmd->cid = cpu_to_le32(0xfffffffe);

	status = aac_fib_send(ContainerCommand,
			  fibctx,
			  sizeof(struct aac_close),
			  FsaNormal,
			  -2 /* Timeout silently */, 1,
			  NULL, NULL);

	if (status >= 0)
		aac_fib_complete(fibctx);
	/* FIB should be freed only after getting the response from the F/W */
	if (status != -ERESTARTSYS)
		aac_fib_free(fibctx);
	return status;
}