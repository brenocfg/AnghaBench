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
struct snd_info_entry {struct gus_proc_private* private_data; } ;
struct gus_proc_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gus_proc_private*) ; 

__attribute__((used)) static void snd_gf1_mem_proc_free(struct snd_info_entry *entry)
{
	struct gus_proc_private *priv = entry->private_data;
	kfree(priv);
}