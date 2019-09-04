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
struct vnode {int dummy; } ;
struct cs_blob {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 struct cs_blob* ubc_cs_blob_get (struct vnode*,int,int /*<<< orphan*/ ) ; 

struct cs_blob *
csvnode_get_blob(struct vnode *vp, off_t offset)
{
	return ubc_cs_blob_get(vp, -1, offset);
}