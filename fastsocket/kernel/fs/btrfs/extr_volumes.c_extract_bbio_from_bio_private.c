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
struct btrfs_bio {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct btrfs_bio *extract_bbio_from_bio_private(void *bi_private)
{
	return (struct btrfs_bio *)(((uintptr_t)bi_private) & ~((uintptr_t)3));
}