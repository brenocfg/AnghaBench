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
struct seq_file {int dummy; } ;
struct ima_template_data {int* digest; int* file_name; } ;
typedef  enum ima_show_type { ____Placeholder_ima_show_type } ima_show_type ;

/* Variables and functions */
 int IMA_DIGEST_SIZE ; 
#define  IMA_SHOW_ASCII 129 
#define  IMA_SHOW_BINARY 128 
 int /*<<< orphan*/  ima_print_digest (struct seq_file*,int*) ; 
 int /*<<< orphan*/  ima_putc (struct seq_file*,int*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int*) ; 
 int strlen (int*) ; 

void ima_template_show(struct seq_file *m, void *e, enum ima_show_type show)
{
	struct ima_template_data *entry = e;
	int namelen;

	switch (show) {
	case IMA_SHOW_ASCII:
		ima_print_digest(m, entry->digest);
		seq_printf(m, " %s\n", entry->file_name);
		break;
	case IMA_SHOW_BINARY:
		ima_putc(m, entry->digest, IMA_DIGEST_SIZE);

		namelen = strlen(entry->file_name);
		ima_putc(m, &namelen, sizeof namelen);
		ima_putc(m, entry->file_name, namelen);
	default:
		break;
	}
}