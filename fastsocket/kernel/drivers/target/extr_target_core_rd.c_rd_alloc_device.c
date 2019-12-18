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
struct se_hba {struct rd_host* hba_ptr; } ;
struct se_device {int dummy; } ;
struct rd_host {int dummy; } ;
struct rd_dev {struct se_device dev; struct rd_host* rd_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct se_device *rd_alloc_device(struct se_hba *hba, const char *name)
{
	struct rd_dev *rd_dev;
	struct rd_host *rd_host = hba->hba_ptr;

	rd_dev = kzalloc(sizeof(struct rd_dev), GFP_KERNEL);
	if (!rd_dev) {
		pr_err("Unable to allocate memory for struct rd_dev\n");
		return NULL;
	}

	rd_dev->rd_host = rd_host;

	return &rd_dev->dev;
}