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
struct debuginfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ debuginfo__init_offline_dwarf (struct debuginfo*,char const*) ; 
 int /*<<< orphan*/  free (struct debuginfo*) ; 
 struct debuginfo* zalloc (int) ; 

struct debuginfo *debuginfo__new(const char *path)
{
	struct debuginfo *self = zalloc(sizeof(struct debuginfo));
	if (!self)
		return NULL;

	if (debuginfo__init_offline_dwarf(self, path) < 0) {
		free(self);
		self = NULL;
	}

	return self;
}