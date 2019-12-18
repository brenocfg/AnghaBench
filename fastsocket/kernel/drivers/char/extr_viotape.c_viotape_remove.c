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
struct vio_dev {int unit_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VIOTAPE_MAJOR ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_class ; 

__attribute__((used)) static int viotape_remove(struct vio_dev *vdev)
{
	int i = vdev->unit_address;

	device_destroy(tape_class, MKDEV(VIOTAPE_MAJOR, i | 0x80));
	device_destroy(tape_class, MKDEV(VIOTAPE_MAJOR, i));
	return 0;
}