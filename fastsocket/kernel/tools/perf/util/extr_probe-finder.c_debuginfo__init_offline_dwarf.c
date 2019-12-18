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
struct debuginfo {scalar_t__ dwfl; int /*<<< orphan*/  dbg; int /*<<< orphan*/  bias; } ;
typedef  int /*<<< orphan*/  Dwfl_Module ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dwfl_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwfl_end (scalar_t__) ; 
 int /*<<< orphan*/  dwfl_module_getdwarf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dwfl_report_offline (scalar_t__,char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct debuginfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offline_callbacks ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debuginfo__init_offline_dwarf(struct debuginfo *self,
					 const char *path)
{
	Dwfl_Module *mod;
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return fd;

	self->dwfl = dwfl_begin(&offline_callbacks);
	if (!self->dwfl)
		goto error;

	mod = dwfl_report_offline(self->dwfl, "", "", fd);
	if (!mod)
		goto error;

	self->dbg = dwfl_module_getdwarf(mod, &self->bias);
	if (!self->dbg)
		goto error;

	return 0;
error:
	if (self->dwfl)
		dwfl_end(self->dwfl);
	else
		close(fd);
	memset(self, 0, sizeof(*self));

	return -ENOENT;
}