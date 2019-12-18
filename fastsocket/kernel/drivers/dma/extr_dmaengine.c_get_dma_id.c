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
struct dma_device {int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_idr ; 
 int /*<<< orphan*/  dma_list_mutex ; 
 int idr_get_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_dma_id(struct dma_device *device)
{
	int rc;

 idr_retry:
	if (!idr_pre_get(&dma_idr, GFP_KERNEL))
		return -ENOMEM;
	mutex_lock(&dma_list_mutex);
	rc = idr_get_new(&dma_idr, NULL, &device->dev_id);
	mutex_unlock(&dma_list_mutex);
	if (rc == -EAGAIN)
		goto idr_retry;
	else if (rc != 0)
		return rc;

	return 0;
}