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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vc_sb; } ;

/* Variables and functions */
 TYPE_1__* coda_vcp (struct super_block*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void coda_put_super(struct super_block *sb)
{
	coda_vcp(sb)->vc_sb = NULL;
	sb->s_fs_info = NULL;

	printk("Coda: Bye bye.\n");
}