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
typedef  int /*<<< orphan*/  vnode_t ;
struct _buf {scalar_t__ _fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  umem_free (struct _buf*,int) ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
kobj_close_file(struct _buf *file)
{
	vn_close((vnode_t *)file->_fd, 0, NULL, NULL);
	umem_free(file, sizeof (struct _buf));
}