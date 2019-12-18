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
struct btrfs_key {void* objectid; int /*<<< orphan*/  type; void* offset; } ;
struct btrfs_disk_key {int /*<<< orphan*/  objectid; int /*<<< orphan*/  type; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_disk_key_to_cpu(struct btrfs_key *cpu,
					 struct btrfs_disk_key *disk)
{
	cpu->offset = le64_to_cpu(disk->offset);
	cpu->type = disk->type;
	cpu->objectid = le64_to_cpu(disk->objectid);
}