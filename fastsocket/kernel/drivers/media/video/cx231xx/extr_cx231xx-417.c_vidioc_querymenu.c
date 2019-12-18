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
struct v4l2_querymenu {int dummy; } ;
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int cx231xx_querymenu (struct cx231xx*,struct v4l2_querymenu*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int vidioc_querymenu(struct file *file, void *priv,
				struct v4l2_querymenu *a)
{
	struct cx231xx_fh  *fh  = priv;
	struct cx231xx *dev = fh->dev;
	dprintk(3, "enter vidioc_querymenu()\n");
	dprintk(3, "exit vidioc_querymenu()\n");
	return cx231xx_querymenu(dev, a);
}