#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char* uuid_string_t ;
typedef  int /*<<< orphan*/  t_name ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  c_name ;
struct TYPE_6__ {int /*<<< orphan*/  p_uuid; int /*<<< orphan*/  p_comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MAXCOMLEN ; 
 TYPE_1__* PROC_NULL ; 
 scalar_t__ escape_str (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  kern_asl_msg (int /*<<< orphan*/ ,char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*,int) ; 
 int proc_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  uuid_unparse_upper (int /*<<< orphan*/ ,char*) ; 

void
fslog_extmod_msgtracer(proc_t caller, proc_t target)
{
	if ((caller != PROC_NULL) && (target != PROC_NULL)) {

		/*
		 * Print into buffer large enough for "ThisIsAnApplicat(BC223DD7-B314-42E0-B6B0-C5D2E6638337)",
		 * including space for escaping, and NUL byte included in sizeof(uuid_string_t).
		 */

		uuid_string_t uuidstr;
		char c_name[2*MAXCOMLEN + 2 /* () */ + sizeof(uuid_string_t)];
		char t_name[2*MAXCOMLEN + 2 /* () */ + sizeof(uuid_string_t)];

		strlcpy(c_name, caller->p_comm, sizeof(c_name));
		uuid_unparse_upper(caller->p_uuid, uuidstr);
		strlcat(c_name, "(", sizeof(c_name));
		strlcat(c_name, uuidstr, sizeof(c_name));
		strlcat(c_name, ")", sizeof(c_name));
		if (0 != escape_str(c_name, strlen(c_name) + 1, sizeof(c_name))) {
			return;
		}

		strlcpy(t_name, target->p_comm, sizeof(t_name));
		uuid_unparse_upper(target->p_uuid, uuidstr);
		strlcat(t_name, "(", sizeof(t_name));
		strlcat(t_name, uuidstr, sizeof(t_name));
		strlcat(t_name, ")", sizeof(t_name));
		if (0 != escape_str(t_name, strlen(t_name) + 1, sizeof(t_name))) {
			return;
		}
#if DEBUG
		printf("EXTMOD: %s(%d) -> %s(%d)\n",
			   c_name,
			   proc_pid(caller),
			   t_name,
			   proc_pid(target));
#endif

		kern_asl_msg(LOG_DEBUG, "messagetracer",
							5,
							"com.apple.message.domain", "com.apple.kernel.external_modification", /* 0 */
							"com.apple.message.signature", c_name, /* 1 */
							"com.apple.message.signature2", t_name, /* 2 */
							"com.apple.message.result", "noop", /* 3 */
							"com.apple.message.summarize", "YES", /* 4 */
							NULL);
	}
}