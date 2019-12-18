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
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct typhoon {int /*<<< orphan*/  curfreq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  typhoon_setfreq (struct typhoon*,int /*<<< orphan*/ ) ; 
 struct typhoon* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct typhoon *dev = video_drvdata(file);

	dev->curfreq = f->frequency;
	typhoon_setfreq(dev, dev->curfreq);
	return 0;
}