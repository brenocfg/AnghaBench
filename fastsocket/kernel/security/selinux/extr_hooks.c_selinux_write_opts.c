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
struct security_mnt_opts {int num_mnt_opts; char** mnt_opts; int* mnt_opts_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CONTEXT_MNT 132 
 char* CONTEXT_STR ; 
#define  DEFCONTEXT_MNT 131 
 char* DEFCONTEXT_STR ; 
#define  FSCONTEXT_MNT 130 
 char* FSCONTEXT_STR ; 
 char* LABELSUPP_STR ; 
#define  ROOTCONTEXT_MNT 129 
 char* ROOTCONTEXT_STR ; 
#define  SE_SBLABELSUPP 128 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void selinux_write_opts(struct seq_file *m,
			       struct security_mnt_opts *opts)
{
	int i;
	char *prefix;

	for (i = 0; i < opts->num_mnt_opts; i++) {
		char *has_comma;

		if (opts->mnt_opts[i])
			has_comma = strchr(opts->mnt_opts[i], ',');
		else
			has_comma = NULL;

		switch (opts->mnt_opts_flags[i]) {
		case CONTEXT_MNT:
			prefix = CONTEXT_STR;
			break;
		case FSCONTEXT_MNT:
			prefix = FSCONTEXT_STR;
			break;
		case ROOTCONTEXT_MNT:
			prefix = ROOTCONTEXT_STR;
			break;
		case DEFCONTEXT_MNT:
			prefix = DEFCONTEXT_STR;
			break;
		case SE_SBLABELSUPP:
			seq_putc(m, ',');
			seq_puts(m, LABELSUPP_STR);
			continue;
		default:
			BUG();
		};
		/* we need a comma before each option */
		seq_putc(m, ',');
		seq_puts(m, prefix);
		if (has_comma)
			seq_putc(m, '\"');
		seq_puts(m, opts->mnt_opts[i]);
		if (has_comma)
			seq_putc(m, '\"');
	}
}