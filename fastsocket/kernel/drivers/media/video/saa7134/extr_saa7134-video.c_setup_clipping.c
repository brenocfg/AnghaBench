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
struct TYPE_2__ {int left; int width; int top; int height; } ;
struct v4l2_clip {TYPE_1__ c; } ;
struct saa7134_dev {int dummy; } ;
struct cliplist {int enable; int disable; void* position; } ;
typedef  int /*<<< orphan*/  row ;
typedef  int /*<<< orphan*/  col ;

/* Variables and functions */
 void* clip_range (int) ; 
 int /*<<< orphan*/  cliplist_cmp ; 
 int /*<<< orphan*/  memset (struct cliplist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cliplist (struct saa7134_dev*,int,struct cliplist*,int,char*) ; 
 int /*<<< orphan*/  sort (struct cliplist*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_clipping(struct saa7134_dev *dev, struct v4l2_clip *clips,
			  int nclips, int interlace)
{
	struct cliplist col[16], row[16];
	int cols = 0, rows = 0, i;
	int div = interlace ? 2 : 1;

	memset(col, 0, sizeof(col));
	memset(row, 0, sizeof(row));
	for (i = 0; i < nclips && i < 8; i++) {
		col[cols].position = clip_range(clips[i].c.left);
		col[cols].enable   = (1 << i);
		cols++;
		col[cols].position = clip_range(clips[i].c.left+clips[i].c.width);
		col[cols].disable  = (1 << i);
		cols++;
		row[rows].position = clip_range(clips[i].c.top / div);
		row[rows].enable   = (1 << i);
		rows++;
		row[rows].position = clip_range((clips[i].c.top + clips[i].c.height)
						/ div);
		row[rows].disable  = (1 << i);
		rows++;
	}
	sort(col, cols, sizeof col[0], cliplist_cmp, NULL);
	sort(row, rows, sizeof row[0], cliplist_cmp, NULL);
	set_cliplist(dev,0x380,col,cols,"cols");
	set_cliplist(dev,0x384,row,rows,"rows");
	return 0;
}