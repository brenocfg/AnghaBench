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
union ubifs_dev_desc {int /*<<< orphan*/  huge; int /*<<< orphan*/  new; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huge_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ new_valid_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ubifs_encode_dev(union ubifs_dev_desc *dev, dev_t rdev)
{
	if (new_valid_dev(rdev)) {
		dev->new = cpu_to_le32(new_encode_dev(rdev));
		return sizeof(dev->new);
	} else {
		dev->huge = cpu_to_le64(huge_encode_dev(rdev));
		return sizeof(dev->huge);
	}
}