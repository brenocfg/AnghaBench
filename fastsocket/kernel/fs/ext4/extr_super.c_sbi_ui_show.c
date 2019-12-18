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
struct ext4_sb_info {int dummy; } ;
struct ext4_attr {int offset; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static ssize_t sbi_ui_show(struct ext4_attr *a,
			   struct ext4_sb_info *sbi, char *buf)
{
	unsigned int *ui = (unsigned int *) (((char *) sbi) + a->offset);

	return snprintf(buf, PAGE_SIZE, "%u\n", *ui);
}