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
typedef  int /*<<< orphan*/  u8 ;
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SECTOR_SIZE ; 
 scalar_t__ get_smart_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  smart_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __idedisk_proc_show(struct seq_file *m, ide_drive_t *drive, u8 sub_cmd)
{
	u8 *buf;

	buf = kmalloc(SECTOR_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	(void)smart_enable(drive);

	if (get_smart_data(drive, buf, sub_cmd) == 0) {
		__le16 *val = (__le16 *)buf;
		int i;

		for (i = 0; i < SECTOR_SIZE / 2; i++) {
			seq_printf(m, "%04x%c", le16_to_cpu(val[i]),
					(i % 8) == 7 ? '\n' : ' ');
		}
	}
	kfree(buf);
	return 0;
}