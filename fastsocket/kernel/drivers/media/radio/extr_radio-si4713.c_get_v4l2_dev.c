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
struct v4l2_device {int dummy; } ;
struct radio_si4713_device {struct v4l2_device v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ video_drvdata (struct file*) ; 

__attribute__((used)) static inline struct v4l2_device *get_v4l2_dev(struct file *file)
{
	return &((struct radio_si4713_device *)video_drvdata(file))->v4l2_dev;
}