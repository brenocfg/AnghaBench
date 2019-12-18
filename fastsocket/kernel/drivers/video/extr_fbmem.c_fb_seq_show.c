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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  node; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fb_seq_show(struct seq_file *m, void *v)
{
	int i = *(loff_t *)v;
	struct fb_info *fi = registered_fb[i];

	if (fi)
		seq_printf(m, "%d %s\n", fi->node, fi->fix.id);
	return 0;
}