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
struct cifsFileInfo {int /*<<< orphan*/  count; } ;

/* Variables and functions */

__attribute__((used)) static inline void
cifsFileInfo_get_locked(struct cifsFileInfo *cifs_file)
{
	++cifs_file->count;
}