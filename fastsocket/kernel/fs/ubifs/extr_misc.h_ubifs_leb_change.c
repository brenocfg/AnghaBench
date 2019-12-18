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
 int ubi_leb_change (int /*<<< orphan*/ ,int,void const*,int,int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int,int,int) ; 

__attribute__((used)) static inline int ubifs_leb_change(const struct ubifs_info *c, int lnum,
				   const void *buf, int len, int dtype)
{
	int err;

	if (c->ro_media)
		return -EROFS;
	err = ubi_leb_change(c->ubi, lnum, buf, len, dtype);
	if (err) {
		ubifs_err("changing %d bytes in LEB %d, error %d",
			  len, lnum, err);
		return err;
	}

	return 0;
}