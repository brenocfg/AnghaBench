#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ti_ohci {TYPE_1__* host; } ;
struct inode {int dummy; } ;
struct file_ctx {int /*<<< orphan*/ * current_ctx; int /*<<< orphan*/  context_list; struct ti_ohci* ohci; } ;
struct file {struct file_ctx* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct ti_ohci* hpsb_get_hostinfo_bykey (int /*<<< orphan*/ *,int) ; 
 int ieee1394_file_to_instance (struct file*) ; 
 struct file_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video1394_highlevel ; 

__attribute__((used)) static int video1394_open(struct inode *inode, struct file *file)
{
	int i = ieee1394_file_to_instance(file);
	struct ti_ohci *ohci;
	struct file_ctx *ctx;

	ohci = hpsb_get_hostinfo_bykey(&video1394_highlevel, i);
        if (ohci == NULL)
                return -EIO;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)  {
		PRINT(KERN_ERR, ohci->host->id, "Cannot malloc file_ctx");
		return -ENOMEM;
	}

	ctx->ohci = ohci;
	INIT_LIST_HEAD(&ctx->context_list);
	ctx->current_ctx = NULL;
	file->private_data = ctx;

	return 0;
}