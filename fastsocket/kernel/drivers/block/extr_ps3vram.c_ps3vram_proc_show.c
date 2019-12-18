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
struct seq_file {struct ps3vram_priv* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  miss; int /*<<< orphan*/  hit; } ;
struct ps3vram_priv {TYPE_1__ cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps3vram_proc_show(struct seq_file *m, void *v)
{
	struct ps3vram_priv *priv = m->private;

	seq_printf(m, "hit:%u\nmiss:%u\n", priv->cache.hit, priv->cache.miss);
	return 0;
}