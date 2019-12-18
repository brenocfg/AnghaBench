#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  void* uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  lr_blkptr; scalar_t__ lr_blkoff; void* lr_length; void* lr_offset; void* lr_foid; } ;
typedef  TYPE_1__ lr_write_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  bcopy (void*,TYPE_1__*,void*) ; 
 TYPE_1__* ztest_lr_alloc (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_lr_free (TYPE_1__*,void*,int /*<<< orphan*/ *) ; 
 int ztest_replay_write (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ztest_write(ztest_ds_t *zd, uint64_t object, uint64_t offset, uint64_t size,
    void *data)
{
	lr_write_t *lr;
	int error;

	lr = ztest_lr_alloc(sizeof (*lr) + size, NULL);

	lr->lr_foid = object;
	lr->lr_offset = offset;
	lr->lr_length = size;
	lr->lr_blkoff = 0;
	BP_ZERO(&lr->lr_blkptr);

	bcopy(data, lr + 1, size);

	error = ztest_replay_write(zd, lr, B_FALSE);

	ztest_lr_free(lr, sizeof (*lr) + size, NULL);

	return (error);
}