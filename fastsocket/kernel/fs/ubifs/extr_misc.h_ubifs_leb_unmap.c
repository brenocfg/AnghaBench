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
struct ubifs_info {int /*<<< orphan*/  ubi; scalar_t__ ro_media; } ;

/* Variables and functions */
 int EROFS ; 
 int ubi_leb_unmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int,int) ; 

__attribute__((used)) static inline int ubifs_leb_unmap(const struct ubifs_info *c, int lnum)
{
	int err;

	if (c->ro_media)
		return -EROFS;
	err = ubi_leb_unmap(c->ubi, lnum);
	if (err) {
		ubifs_err("unmap LEB %d failed, error %d", lnum, err);
		return err;
	}

	return 0;
}