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
struct perf_kvm_stat {char* file_name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int ENOMEM ; 
 char* STRDUP_FAIL_EXIT (char*) ; 
 char** calloc (unsigned int,int) ; 
 int cmd_record (unsigned int,char const**,int /*<<< orphan*/ *) ; 
 char** record_args ; 

__attribute__((used)) static int
kvm_events_record(struct perf_kvm_stat *kvm, int argc, const char **argv)
{
	unsigned int rec_argc, i, j;
	const char **rec_argv;

	rec_argc = ARRAY_SIZE(record_args) + argc + 2;
	rec_argv = calloc(rec_argc + 1, sizeof(char *));

	if (rec_argv == NULL)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(record_args); i++)
		rec_argv[i] = STRDUP_FAIL_EXIT(record_args[i]);

	rec_argv[i++] = STRDUP_FAIL_EXIT("-o");
	rec_argv[i++] = STRDUP_FAIL_EXIT(kvm->file_name);

	for (j = 1; j < (unsigned int)argc; j++, i++)
		rec_argv[i] = argv[j];

	return cmd_record(i, rec_argv, NULL);
}