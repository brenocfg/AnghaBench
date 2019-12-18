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
struct cifs_ses {struct cifs_ses* domainName; struct cifs_ses* user_name; struct cifs_ses* password; struct cifs_ses* serverNOS; struct cifs_ses* serverDomain; struct cifs_ses* serverOS; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  kfree (struct cifs_ses*) ; 
 int /*<<< orphan*/  memset (struct cifs_ses*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sesInfoAllocCount ; 
 int /*<<< orphan*/  strlen (struct cifs_ses*) ; 

void
sesInfoFree(struct cifs_ses *buf_to_free)
{
	if (buf_to_free == NULL) {
		cFYI(1, "Null buffer passed to sesInfoFree");
		return;
	}

	atomic_dec(&sesInfoAllocCount);
	kfree(buf_to_free->serverOS);
	kfree(buf_to_free->serverDomain);
	kfree(buf_to_free->serverNOS);
	if (buf_to_free->password) {
		memset(buf_to_free->password, 0, strlen(buf_to_free->password));
		kfree(buf_to_free->password);
	}
	kfree(buf_to_free->user_name);
	kfree(buf_to_free->domainName);
	kfree(buf_to_free);
}