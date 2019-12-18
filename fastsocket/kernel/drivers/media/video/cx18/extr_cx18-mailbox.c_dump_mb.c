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
struct cx18_mailbox {int /*<<< orphan*/  args; int /*<<< orphan*/  error; int /*<<< orphan*/  cmd; int /*<<< orphan*/  ack; int /*<<< orphan*/  request; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int CX18_DBGFLG_API ; 
 int /*<<< orphan*/  CX18_DEBUG_API (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_MB_ARGUMENTS ; 
 int cx18_debug ; 
 int /*<<< orphan*/  u32arr2hex (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void dump_mb(struct cx18 *cx, struct cx18_mailbox *mb, char *name)
{
	char argstr[MAX_MB_ARGUMENTS*11+1];

	if (!(cx18_debug & CX18_DBGFLG_API))
		return;

	CX18_DEBUG_API("%s: req %#010x ack %#010x cmd %#010x err %#010x args%s"
		       "\n", name, mb->request, mb->ack, mb->cmd, mb->error,
		       u32arr2hex(mb->args, MAX_MB_ARGUMENTS, argstr));
}