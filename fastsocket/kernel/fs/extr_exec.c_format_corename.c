#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; } ;
struct cred {long uid; long gid; } ;
struct core_name {int size; int /*<<< orphan*/  corename; scalar_t__ used; } ;
struct TYPE_5__ {long comm; } ;
struct TYPE_4__ {long nodename; } ;

/* Variables and functions */
 int CORENAME_MAX_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_count ; 
 int cn_print_exe_file (struct core_name*) ; 
 int cn_printf (struct core_name*,char*,long) ; 
 char* core_pattern ; 
 scalar_t__ core_uses_pid ; 
 TYPE_2__* current ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 long rlimit (int /*<<< orphan*/ ) ; 
 long task_tgid_vnr (TYPE_2__*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uts_sem ; 
 TYPE_1__* utsname () ; 

__attribute__((used)) static int format_corename(struct core_name *cn, long signr)
{
	const struct cred *cred = current_cred();
	const char *pat_ptr = core_pattern;
	int ispipe = (*pat_ptr == '|');
	int pid_in_pattern = 0;

	int err = 0;

	cn->size = CORENAME_MAX_SIZE * atomic_read(&call_count);
	cn->corename = kmalloc(cn->size, GFP_KERNEL);
	cn->used = 0;

	if (!cn->corename)
		return -ENOMEM;

	/* Repeat as long as we have more pattern to process and more output
	   space */
	while (*pat_ptr) {
		if (*pat_ptr != '%') {
			if (*pat_ptr == 0)
				goto out;
			err = cn_printf(cn, "%c", *pat_ptr++);
		} else {
			switch (*++pat_ptr) {
			/* single % at the end, drop that */
			case 0:
				goto out;
			/* Double percent, output one percent */
			case '%':
				err = cn_printf(cn, "%c", '%');
				break;
			/* pid */
			case 'p':
				pid_in_pattern = 1;
				err = cn_printf(cn, "%d",
					      task_tgid_vnr(current));
				break;
			/* uid */
			case 'u':
				err = cn_printf(cn, "%d", cred->uid);
				break;
			/* gid */
			case 'g':
				err = cn_printf(cn, "%d", cred->gid);
				break;
			/* signal that caused the coredump */
			case 's':
				err = cn_printf(cn, "%ld", signr);
				break;
			/* UNIX time of coredump */
			case 't': {
				struct timeval tv;
				do_gettimeofday(&tv);
				err = cn_printf(cn, "%lu", tv.tv_sec);
				break;
			}
			/* hostname */
			case 'h':
				down_read(&uts_sem);
				err = cn_printf(cn, "%s",
					      utsname()->nodename);
				up_read(&uts_sem);
				break;
			/* executable */
			case 'e':
				err = cn_printf(cn, "%s", current->comm);
				break;
			case 'E':
				err = cn_print_exe_file(cn);
				break;
			/* core limit size */
			case 'c':
				err = cn_printf(cn, "%lu",
					      rlimit(RLIMIT_CORE));
				break;
			default:
				break;
			}
			++pat_ptr;
		}

		if (err)
			return err;
	}
	/* Backward compatibility with core_uses_pid:
	 *
	 * If core_pattern does not include a %p (as is the default)
	 * and core_uses_pid is set, then .%pid will be appended to
	 * the filename. Do not do this for piped commands. */
	if (!ispipe && !pid_in_pattern && core_uses_pid) {
		err = cn_printf(cn, ".%d", task_tgid_vnr(current));
		if (err)
			return err;
	}
out:
	return ispipe;
}