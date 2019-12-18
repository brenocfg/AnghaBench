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
struct cardstate {TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_cmd ) (struct cardstate*,char*,size_t,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct cardstate*,char*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void send_command(struct cardstate *cs, const char *cmd, int cid,
			 int dle, gfp_t kmallocflags)
{
	size_t cmdlen, buflen;
	char *cmdpos, *cmdbuf, *cmdtail;

	cmdlen = strlen(cmd);
	buflen = 11 + cmdlen;
	if (unlikely(buflen <= cmdlen)) {
		dev_err(cs->dev, "integer overflow in buflen\n");
		return;
	}

	cmdbuf = kmalloc(buflen, kmallocflags);
	if (unlikely(!cmdbuf)) {
		dev_err(cs->dev, "out of memory\n");
		return;
	}

	cmdpos = cmdbuf + 9;
	cmdtail = cmdpos + cmdlen;
	memcpy(cmdpos, cmd, cmdlen);

	if (cid > 0 && cid <= 65535) {
		do {
			*--cmdpos = '0' + cid % 10;
			cid /= 10;
			++cmdlen;
		} while (cid);
	}

	cmdlen += 2;
	*--cmdpos = 'T';
	*--cmdpos = 'A';

	if (dle) {
		cmdlen += 4;
		*--cmdpos = '(';
		*--cmdpos = 0x10;
		*cmdtail++ = 0x10;
		*cmdtail++ = ')';
	}

	cs->ops->write_cmd(cs, cmdpos, cmdlen, NULL);
	kfree(cmdbuf);
}