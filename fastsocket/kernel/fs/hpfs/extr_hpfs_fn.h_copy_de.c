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
struct hpfs_dirent {int down; int not_8x3; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static inline void copy_de(struct hpfs_dirent *dst, struct hpfs_dirent *src)
{
	int a;
	int n;
	if (!dst || !src) return;
	a = dst->down;
	n = dst->not_8x3;
	memcpy((char *)dst + 2, (char *)src + 2, 28);
	dst->down = a;
	dst->not_8x3 = n;
}