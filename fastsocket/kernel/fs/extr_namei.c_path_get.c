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
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntget (int /*<<< orphan*/ ) ; 

void path_get(struct path *path)
{
	mntget(path->mnt);
	dget(path->dentry);
}