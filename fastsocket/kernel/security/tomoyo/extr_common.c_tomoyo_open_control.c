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
typedef  int u8 ;
struct tomoyo_io_buffer {int readbuf_size; int writebuf_size; struct tomoyo_io_buffer* read_buf; void* write_buf; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; int /*<<< orphan*/  io_sem; } ;
struct file {int f_mode; struct tomoyo_io_buffer* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
#define  TOMOYO_DOMAINPOLICY 136 
#define  TOMOYO_DOMAIN_STATUS 135 
#define  TOMOYO_EXCEPTIONPOLICY 134 
#define  TOMOYO_MANAGER 133 
#define  TOMOYO_MEMINFO 132 
#define  TOMOYO_PROCESS_STATUS 131 
#define  TOMOYO_PROFILE 130 
#define  TOMOYO_SELFDOMAIN 129 
#define  TOMOYO_VERSION 128 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* tomoyo_alloc (int) ; 
 int /*<<< orphan*/  tomoyo_free (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  tomoyo_read_control (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tomoyo_read_domain_policy ; 
 int /*<<< orphan*/ * tomoyo_read_domain_profile ; 
 int /*<<< orphan*/ * tomoyo_read_exception_policy ; 
 int /*<<< orphan*/ * tomoyo_read_manager_policy ; 
 int /*<<< orphan*/ * tomoyo_read_memory_counter ; 
 int /*<<< orphan*/ * tomoyo_read_pid ; 
 int /*<<< orphan*/ * tomoyo_read_profile ; 
 int /*<<< orphan*/ * tomoyo_read_self_domain ; 
 int /*<<< orphan*/ * tomoyo_read_version ; 
 int /*<<< orphan*/ * tomoyo_write_domain_policy ; 
 int /*<<< orphan*/ * tomoyo_write_domain_profile ; 
 int /*<<< orphan*/ * tomoyo_write_exception_policy ; 
 int /*<<< orphan*/ * tomoyo_write_manager_policy ; 
 int /*<<< orphan*/ * tomoyo_write_memory_quota ; 
 int /*<<< orphan*/ * tomoyo_write_pid ; 
 int /*<<< orphan*/ * tomoyo_write_profile ; 

__attribute__((used)) static int tomoyo_open_control(const u8 type, struct file *file)
{
	struct tomoyo_io_buffer *head = tomoyo_alloc(sizeof(*head));

	if (!head)
		return -ENOMEM;
	mutex_init(&head->io_sem);
	switch (type) {
	case TOMOYO_DOMAINPOLICY:
		/* /sys/kernel/security/tomoyo/domain_policy */
		head->write = tomoyo_write_domain_policy;
		head->read = tomoyo_read_domain_policy;
		break;
	case TOMOYO_EXCEPTIONPOLICY:
		/* /sys/kernel/security/tomoyo/exception_policy */
		head->write = tomoyo_write_exception_policy;
		head->read = tomoyo_read_exception_policy;
		break;
	case TOMOYO_SELFDOMAIN:
		/* /sys/kernel/security/tomoyo/self_domain */
		head->read = tomoyo_read_self_domain;
		break;
	case TOMOYO_DOMAIN_STATUS:
		/* /sys/kernel/security/tomoyo/.domain_status */
		head->write = tomoyo_write_domain_profile;
		head->read = tomoyo_read_domain_profile;
		break;
	case TOMOYO_PROCESS_STATUS:
		/* /sys/kernel/security/tomoyo/.process_status */
		head->write = tomoyo_write_pid;
		head->read = tomoyo_read_pid;
		break;
	case TOMOYO_VERSION:
		/* /sys/kernel/security/tomoyo/version */
		head->read = tomoyo_read_version;
		head->readbuf_size = 128;
		break;
	case TOMOYO_MEMINFO:
		/* /sys/kernel/security/tomoyo/meminfo */
		head->write = tomoyo_write_memory_quota;
		head->read = tomoyo_read_memory_counter;
		head->readbuf_size = 512;
		break;
	case TOMOYO_PROFILE:
		/* /sys/kernel/security/tomoyo/profile */
		head->write = tomoyo_write_profile;
		head->read = tomoyo_read_profile;
		break;
	case TOMOYO_MANAGER:
		/* /sys/kernel/security/tomoyo/manager */
		head->write = tomoyo_write_manager_policy;
		head->read = tomoyo_read_manager_policy;
		break;
	}
	if (!(file->f_mode & FMODE_READ)) {
		/*
		 * No need to allocate read_buf since it is not opened
		 * for reading.
		 */
		head->read = NULL;
	} else {
		if (!head->readbuf_size)
			head->readbuf_size = 4096 * 2;
		head->read_buf = tomoyo_alloc(head->readbuf_size);
		if (!head->read_buf) {
			tomoyo_free(head);
			return -ENOMEM;
		}
	}
	if (!(file->f_mode & FMODE_WRITE)) {
		/*
		 * No need to allocate write_buf since it is not opened
		 * for writing.
		 */
		head->write = NULL;
	} else if (head->write) {
		head->writebuf_size = 4096 * 2;
		head->write_buf = tomoyo_alloc(head->writebuf_size);
		if (!head->write_buf) {
			tomoyo_free(head->read_buf);
			tomoyo_free(head);
			return -ENOMEM;
		}
	}
	file->private_data = head;
	/*
	 * Call the handler now if the file is
	 * /sys/kernel/security/tomoyo/self_domain
	 * so that the user can use
	 * cat < /sys/kernel/security/tomoyo/self_domain"
	 * to know the current process's domainname.
	 */
	if (type == TOMOYO_SELFDOMAIN)
		tomoyo_read_control(file, NULL, 0);
	return 0;
}