#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ buf_end; scalar_t__ buf_pos; int /*<<< orphan*/  fd; int /*<<< orphan*/  tell; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

void seekdir(DIR *dir, long off)
{
	LOCK(dir->lock);
	dir->tell = lseek(dir->fd, off, SEEK_SET);
	dir->buf_pos = dir->buf_end = 0;
	UNLOCK(dir->lock);
}