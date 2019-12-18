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
struct block_device {int dummy; } ;
struct blk_integrity {int flags; int /*<<< orphan*/ * generate_fn; int /*<<< orphan*/ * verify_fn; } ;

/* Variables and functions */
 int INTEGRITY_FLAG_READ ; 
 int INTEGRITY_FLAG_WRITE ; 
 int READ ; 
 int WRITE ; 
 struct blk_integrity* bdev_get_integrity (struct block_device*) ; 

__attribute__((used)) static int bdev_integrity_enabled(struct block_device *bdev, int rw)
{
	struct blk_integrity *bi = bdev_get_integrity(bdev);

	if (bi == NULL)
		return 0;

	if (rw == READ && bi->verify_fn != NULL &&
	    (bi->flags & INTEGRITY_FLAG_READ))
		return 1;

	if (rw == WRITE && bi->generate_fn != NULL &&
	    (bi->flags & INTEGRITY_FLAG_WRITE))
		return 1;

	return 0;
}