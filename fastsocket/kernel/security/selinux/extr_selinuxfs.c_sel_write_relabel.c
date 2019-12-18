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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct file {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SECURITY__COMPUTE_RELABEL ; 
 int SIMPLE_TRANSACTION_LIMIT ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int security_change_sid (int,int,int /*<<< orphan*/ ,int*) ; 
 int security_context_to_sid (char*,scalar_t__,int*) ; 
 int security_sid_to_context (int,char**,int*) ; 
 int sscanf (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int task_has_security (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sel_write_relabel(struct file *file, char *buf, size_t size)
{
	char *scon, *tcon;
	u32 ssid, tsid, newsid;
	u16 tclass;
	ssize_t length;
	char *newcon;
	u32 len;

	length = task_has_security(current, SECURITY__COMPUTE_RELABEL);
	if (length)
		return length;

	length = -ENOMEM;
	scon = kzalloc(size+1, GFP_KERNEL);
	if (!scon)
		return length;

	tcon = kzalloc(size+1, GFP_KERNEL);
	if (!tcon)
		goto out;

	length = -EINVAL;
	if (sscanf(buf, "%s %s %hu", scon, tcon, &tclass) != 3)
		goto out2;

	length = security_context_to_sid(scon, strlen(scon)+1, &ssid);
	if (length < 0)
		goto out2;
	length = security_context_to_sid(tcon, strlen(tcon)+1, &tsid);
	if (length < 0)
		goto out2;

	length = security_change_sid(ssid, tsid, tclass, &newsid);
	if (length < 0)
		goto out2;

	length = security_sid_to_context(newsid, &newcon, &len);
	if (length < 0)
		goto out2;

	if (len > SIMPLE_TRANSACTION_LIMIT) {
		length = -ERANGE;
		goto out3;
	}

	memcpy(buf, newcon, len);
	length = len;
out3:
	kfree(newcon);
out2:
	kfree(tcon);
out:
	kfree(scon);
	return length;
}