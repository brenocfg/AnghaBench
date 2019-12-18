#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vivi_fh {struct vivi_dev* dev; } ;
struct vivi_dev {int ms; int s; int m; int h; int /*<<< orphan*/  timestr; scalar_t__ jiffies; int /*<<< orphan*/  mv_count; } ;
struct timeval {int dummy; } ;
struct TYPE_2__ {int height; int width; int /*<<< orphan*/  state; struct timeval ts; int /*<<< orphan*/  field_count; } ;
struct vivi_buffer {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  dprintk (struct vivi_dev*,int,char*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  gen_line (struct vivi_fh*,char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 void* videobuf_to_vmalloc (TYPE_1__*) ; 

__attribute__((used)) static void vivi_fillbuff(struct vivi_fh *fh, struct vivi_buffer *buf)
{
	struct vivi_dev *dev = fh->dev;
	int h , pos = 0;
	int hmax  = buf->vb.height;
	int wmax  = buf->vb.width;
	struct timeval ts;
	char *tmpbuf;
	void *vbuf = videobuf_to_vmalloc(&buf->vb);

	if (!vbuf)
		return;

	tmpbuf = kmalloc(wmax * 2, GFP_ATOMIC);
	if (!tmpbuf)
		return;

	for (h = 0; h < hmax; h++) {
		gen_line(fh, tmpbuf, 0, wmax, hmax, h, dev->mv_count,
			 dev->timestr);
		memcpy(vbuf + pos, tmpbuf, wmax * 2);
		pos += wmax*2;
	}

	dev->mv_count++;

	kfree(tmpbuf);

	/* Updates stream time */

	dev->ms += jiffies_to_msecs(jiffies-dev->jiffies);
	dev->jiffies = jiffies;
	if (dev->ms >= 1000) {
		dev->ms -= 1000;
		dev->s++;
		if (dev->s >= 60) {
			dev->s -= 60;
			dev->m++;
			if (dev->m > 60) {
				dev->m -= 60;
				dev->h++;
				if (dev->h > 24)
					dev->h -= 24;
			}
		}
	}
	sprintf(dev->timestr, "%02d:%02d:%02d:%03d",
			dev->h, dev->m, dev->s, dev->ms);

	dprintk(dev, 2, "vivifill at %s: Buffer 0x%08lx size= %d\n",
			dev->timestr, (unsigned long)tmpbuf, pos);

	/* Advice that buffer was filled */
	buf->vb.field_count++;
	do_gettimeofday(&ts);
	buf->vb.ts = ts;
	buf->vb.state = VIDEOBUF_DONE;
}