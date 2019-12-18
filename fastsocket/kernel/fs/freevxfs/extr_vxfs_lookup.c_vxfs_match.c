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
struct vxfs_direct {int d_namelen; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char const* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
vxfs_match(int len, const char * const name, struct vxfs_direct *de)
{
	if (len != de->d_namelen)
		return 0;
	if (!de->d_ino)
		return 0;
	return !memcmp(name, de->d_name, len);
}