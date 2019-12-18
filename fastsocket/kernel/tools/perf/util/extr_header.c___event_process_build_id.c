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
typedef  int u16 ;
struct perf_session {int dummy; } ;
struct list_head {int dummy; } ;
struct machine {struct list_head user_dsos; struct list_head kernel_dsos; } ;
struct dso {int kernel; int /*<<< orphan*/  long_name; int /*<<< orphan*/  build_id; } ;
struct TYPE_2__ {int misc; } ;
struct build_id_event {int /*<<< orphan*/  build_id; TYPE_1__ header; int /*<<< orphan*/  pid; } ;
typedef  enum dso_kernel_type { ____Placeholder_dso_kernel_type } dso_kernel_type ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int DSO_TYPE_GUEST_KERNEL ; 
 int DSO_TYPE_KERNEL ; 
 int DSO_TYPE_USER ; 
 int PERF_RECORD_MISC_CPUMODE_MASK ; 
#define  PERF_RECORD_MISC_GUEST_KERNEL 131 
#define  PERF_RECORD_MISC_GUEST_USER 130 
#define  PERF_RECORD_MISC_KERNEL 129 
#define  PERF_RECORD_MISC_USER 128 
 struct dso* __dsos__findnew (struct list_head*,char*) ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  dso__set_build_id (struct dso*,int /*<<< orphan*/ *) ; 
 struct machine* perf_session__findnew_machine (struct perf_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int __event_process_build_id(struct build_id_event *bev,
				    char *filename,
				    struct perf_session *session)
{
	int err = -1;
	struct list_head *head;
	struct machine *machine;
	u16 misc;
	struct dso *dso;
	enum dso_kernel_type dso_type;

	machine = perf_session__findnew_machine(session, bev->pid);
	if (!machine)
		goto out;

	misc = bev->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;

	switch (misc) {
	case PERF_RECORD_MISC_KERNEL:
		dso_type = DSO_TYPE_KERNEL;
		head = &machine->kernel_dsos;
		break;
	case PERF_RECORD_MISC_GUEST_KERNEL:
		dso_type = DSO_TYPE_GUEST_KERNEL;
		head = &machine->kernel_dsos;
		break;
	case PERF_RECORD_MISC_USER:
	case PERF_RECORD_MISC_GUEST_USER:
		dso_type = DSO_TYPE_USER;
		head = &machine->user_dsos;
		break;
	default:
		goto out;
	}

	dso = __dsos__findnew(head, filename);
	if (dso != NULL) {
		char sbuild_id[BUILD_ID_SIZE * 2 + 1];

		dso__set_build_id(dso, &bev->build_id);

		if (filename[0] == '[')
			dso->kernel = dso_type;

		build_id__sprintf(dso->build_id, sizeof(dso->build_id),
				  sbuild_id);
		pr_debug("build id event received for %s: %s\n",
			 dso->long_name, sbuild_id);
	}

	err = 0;
out:
	return err;
}