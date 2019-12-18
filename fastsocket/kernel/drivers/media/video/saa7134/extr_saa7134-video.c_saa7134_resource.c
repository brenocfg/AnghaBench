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
struct saa7134_fh {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int RESOURCE_VBI ; 
 int RESOURCE_VIDEO ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static int saa7134_resource(struct saa7134_fh *fh)
{
	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return RESOURCE_VIDEO;

	if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		return RESOURCE_VBI;

	BUG();
	return 0;
}