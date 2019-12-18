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
typedef  int u_long ;
struct sym_usrcmd {int cmd; int target; int data; } ;
struct sym_hcb {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int DEBUG_ALLOC ; 
 int DEBUG_NEGO ; 
 int DEBUG_PHASE ; 
 int DEBUG_POINTER ; 
 int DEBUG_QUEUE ; 
 int DEBUG_RESULT ; 
 int DEBUG_SCATTER ; 
 int DEBUG_SCRIPT ; 
 int DEBUG_TAGS ; 
 int DEBUG_TIMING ; 
 int DEBUG_TINY ; 
 int EINVAL ; 
 int /*<<< orphan*/  GET_INT_ARG (char*,int,int) ; 
 int /*<<< orphan*/  SKIP_SPACES (char*,int) ; 
 int SYM_DISC_ENABLED ; 
#define  UC_CLEARDEV 135 
#define  UC_RESETDEV 134 
#define  UC_SETDEBUG 133 
#define  UC_SETFLAG 132 
#define  UC_SETSYNC 131 
#define  UC_SETTAGS 130 
#define  UC_SETVERBOSE 129 
#define  UC_SETWIDE 128 
 int is_keyword (char*,int,char*) ; 
 int /*<<< orphan*/  memset (struct sym_usrcmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sym_exec_user_command (struct sym_hcb*,struct sym_usrcmd*) ; 
 struct sym_hcb* sym_get_hcb (struct Scsi_Host*) ; 

__attribute__((used)) static int sym_user_command(struct Scsi_Host *shost, char *buffer, int length)
{
	struct sym_hcb *np = sym_get_hcb(shost);
	char *ptr	= buffer;
	int len		= length;
	struct sym_usrcmd cmd, *uc = &cmd;
	int		arg_len;
	u_long 		target;

	memset(uc, 0, sizeof(*uc));

	if (len > 0 && ptr[len-1] == '\n')
		--len;

	if	((arg_len = is_keyword(ptr, len, "setsync")) != 0)
		uc->cmd = UC_SETSYNC;
	else if	((arg_len = is_keyword(ptr, len, "settags")) != 0)
		uc->cmd = UC_SETTAGS;
	else if	((arg_len = is_keyword(ptr, len, "setverbose")) != 0)
		uc->cmd = UC_SETVERBOSE;
	else if	((arg_len = is_keyword(ptr, len, "setwide")) != 0)
		uc->cmd = UC_SETWIDE;
#ifdef SYM_LINUX_DEBUG_CONTROL_SUPPORT
	else if	((arg_len = is_keyword(ptr, len, "setdebug")) != 0)
		uc->cmd = UC_SETDEBUG;
#endif
	else if	((arg_len = is_keyword(ptr, len, "setflag")) != 0)
		uc->cmd = UC_SETFLAG;
	else if	((arg_len = is_keyword(ptr, len, "resetdev")) != 0)
		uc->cmd = UC_RESETDEV;
	else if	((arg_len = is_keyword(ptr, len, "cleardev")) != 0)
		uc->cmd = UC_CLEARDEV;
	else
		arg_len = 0;

#ifdef DEBUG_PROC_INFO
printk("sym_user_command: arg_len=%d, cmd=%ld\n", arg_len, uc->cmd);
#endif

	if (!arg_len)
		return -EINVAL;
	ptr += arg_len; len -= arg_len;

	switch(uc->cmd) {
	case UC_SETSYNC:
	case UC_SETTAGS:
	case UC_SETWIDE:
	case UC_SETFLAG:
	case UC_RESETDEV:
	case UC_CLEARDEV:
		SKIP_SPACES(ptr, len);
		if ((arg_len = is_keyword(ptr, len, "all")) != 0) {
			ptr += arg_len; len -= arg_len;
			uc->target = ~0;
		} else {
			GET_INT_ARG(ptr, len, target);
			uc->target = (1<<target);
#ifdef DEBUG_PROC_INFO
printk("sym_user_command: target=%ld\n", target);
#endif
		}
		break;
	}

	switch(uc->cmd) {
	case UC_SETVERBOSE:
	case UC_SETSYNC:
	case UC_SETTAGS:
	case UC_SETWIDE:
		SKIP_SPACES(ptr, len);
		GET_INT_ARG(ptr, len, uc->data);
#ifdef DEBUG_PROC_INFO
printk("sym_user_command: data=%ld\n", uc->data);
#endif
		break;
#ifdef SYM_LINUX_DEBUG_CONTROL_SUPPORT
	case UC_SETDEBUG:
		while (len > 0) {
			SKIP_SPACES(ptr, len);
			if	((arg_len = is_keyword(ptr, len, "alloc")))
				uc->data |= DEBUG_ALLOC;
			else if	((arg_len = is_keyword(ptr, len, "phase")))
				uc->data |= DEBUG_PHASE;
			else if	((arg_len = is_keyword(ptr, len, "queue")))
				uc->data |= DEBUG_QUEUE;
			else if	((arg_len = is_keyword(ptr, len, "result")))
				uc->data |= DEBUG_RESULT;
			else if	((arg_len = is_keyword(ptr, len, "scatter")))
				uc->data |= DEBUG_SCATTER;
			else if	((arg_len = is_keyword(ptr, len, "script")))
				uc->data |= DEBUG_SCRIPT;
			else if	((arg_len = is_keyword(ptr, len, "tiny")))
				uc->data |= DEBUG_TINY;
			else if	((arg_len = is_keyword(ptr, len, "timing")))
				uc->data |= DEBUG_TIMING;
			else if	((arg_len = is_keyword(ptr, len, "nego")))
				uc->data |= DEBUG_NEGO;
			else if	((arg_len = is_keyword(ptr, len, "tags")))
				uc->data |= DEBUG_TAGS;
			else if	((arg_len = is_keyword(ptr, len, "pointer")))
				uc->data |= DEBUG_POINTER;
			else
				return -EINVAL;
			ptr += arg_len; len -= arg_len;
		}
#ifdef DEBUG_PROC_INFO
printk("sym_user_command: data=%ld\n", uc->data);
#endif
		break;
#endif /* SYM_LINUX_DEBUG_CONTROL_SUPPORT */
	case UC_SETFLAG:
		while (len > 0) {
			SKIP_SPACES(ptr, len);
			if	((arg_len = is_keyword(ptr, len, "no_disc")))
				uc->data &= ~SYM_DISC_ENABLED;
			else
				return -EINVAL;
			ptr += arg_len; len -= arg_len;
		}
		break;
	default:
		break;
	}

	if (len)
		return -EINVAL;
	else {
		unsigned long flags;

		spin_lock_irqsave(shost->host_lock, flags);
		sym_exec_user_command(np, uc);
		spin_unlock_irqrestore(shost->host_lock, flags);
	}
	return length;
}