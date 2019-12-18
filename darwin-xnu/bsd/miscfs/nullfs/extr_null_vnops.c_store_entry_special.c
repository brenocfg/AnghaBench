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
struct uio {int dummy; } ;
struct dirent {size_t d_namlen; scalar_t__ d_reclen; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_ino; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  e ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ DIRENT_SZ (struct dirent*) ; 
 int /*<<< orphan*/  DT_DIR ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 size_t NAME_MAX ; 
 int /*<<< orphan*/  memset (struct dirent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ uio_resid (struct uio*) ; 
 int uiomove (int /*<<< orphan*/ ,scalar_t__,struct uio*) ; 

__attribute__((used)) static int
store_entry_special(ino_t ino, const char * name, struct uio * uio)
{
	struct dirent e;
	size_t namelen = strlen(name);
	int error      = EINVAL;

	if (namelen + 1 <= NAME_MAX) {
		memset(&e, 0, sizeof(e));

		e.d_ino  = ino;
		e.d_type = DT_DIR;

		e.d_namlen = namelen; /* don't include NUL */
		e.d_reclen = DIRENT_SZ(&e);
		if (uio_resid(uio) >= e.d_reclen) {
			strlcpy(e.d_name, name, NAME_MAX);
			error = uiomove((caddr_t)&e, e.d_reclen, uio);
		} else {
			error = EMSGSIZE;
		}
	}
	return error;
}