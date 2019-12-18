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
struct cifs_tcon {struct cifs_tcon* password; struct cifs_tcon* nativeFileSystem; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  kfree (struct cifs_tcon*) ; 
 int /*<<< orphan*/  memset (struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (struct cifs_tcon*) ; 
 int /*<<< orphan*/  tconInfoAllocCount ; 

void
tconInfoFree(struct cifs_tcon *buf_to_free)
{
	if (buf_to_free == NULL) {
		cFYI(1, "Null buffer passed to tconInfoFree");
		return;
	}
	atomic_dec(&tconInfoAllocCount);
	kfree(buf_to_free->nativeFileSystem);
	if (buf_to_free->password) {
		memset(buf_to_free->password, 0, strlen(buf_to_free->password));
		kfree(buf_to_free->password);
	}
	kfree(buf_to_free);
}