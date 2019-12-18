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
struct inode {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 char* inode_name (struct inode*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *inode_dentry_name(struct inode *ino, struct dentry *dentry)
{
	char *file;
	int len;

	file = inode_name(ino, dentry->d_name.len + 1);
	if (file == NULL)
		return NULL;
	strcat(file, "/");
	len = strlen(file);
	strncat(file, dentry->d_name.name, dentry->d_name.len);
	file[len + dentry->d_name.len] = '\0';
	return file;
}