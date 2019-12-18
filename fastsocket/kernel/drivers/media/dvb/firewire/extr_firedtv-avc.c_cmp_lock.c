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
typedef  int /*<<< orphan*/  u64 ;
struct firedtv {int /*<<< orphan*/  avc_mutex; int /*<<< orphan*/ * avc_data; int /*<<< orphan*/  device; TYPE_1__* backend; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int (* lock ) (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmp_lock(struct firedtv *fdtv, u64 addr, __be32 data[])
{
	int ret;

	mutex_lock(&fdtv->avc_mutex);

	/* data[] is stack-allocated and should not be DMA-mapped. */
	memcpy(fdtv->avc_data, data, 8);

	ret = fdtv->backend->lock(fdtv, addr, fdtv->avc_data);
	if (ret < 0)
		dev_err(fdtv->device, "CMP: lock I/O error\n");
	else
		memcpy(data, fdtv->avc_data, 8);

	mutex_unlock(&fdtv->avc_mutex);

	return ret;
}