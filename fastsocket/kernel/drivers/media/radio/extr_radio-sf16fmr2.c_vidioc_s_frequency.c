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
struct v4l2_frequency {int frequency; } ;
struct fmr2 {int curfreq; int /*<<< orphan*/  lock; int /*<<< orphan*/  mute; scalar_t__ curvol; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RSF16_MAXFREQ ; 
 int RSF16_MINFREQ ; 
 int /*<<< orphan*/  fmr2_setfreq (struct fmr2*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fmr2* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct fmr2 *fmr2 = video_drvdata(file);

	if (f->frequency < RSF16_MINFREQ ||
			f->frequency > RSF16_MAXFREQ)
		return -EINVAL;
	/* rounding in steps of 200 to match the freq
	   that will be used */
	fmr2->curfreq = (f->frequency / 200) * 200;

	/* set card freq (if not muted) */
	if (fmr2->curvol && !fmr2->mute) {
		mutex_lock(&fmr2->lock);
		fmr2_setfreq(fmr2);
		mutex_unlock(&fmr2->lock);
	}
	return 0;
}