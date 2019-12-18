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
struct cifsFileInfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifsFileInfo_get_locked (struct cifsFileInfo*) ; 
 int /*<<< orphan*/  cifs_file_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct cifsFileInfo *
cifsFileInfo_get(struct cifsFileInfo *cifs_file)
{
	spin_lock(&cifs_file_list_lock);
	cifsFileInfo_get_locked(cifs_file);
	spin_unlock(&cifs_file_list_lock);
	return cifs_file;
}