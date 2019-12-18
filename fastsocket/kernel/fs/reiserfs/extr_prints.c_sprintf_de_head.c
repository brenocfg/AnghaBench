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
struct reiserfs_de_head {int dummy; } ;

/* Variables and functions */
 int deh_dir_id (struct reiserfs_de_head*) ; 
 int deh_location (struct reiserfs_de_head*) ; 
 int deh_objectid (struct reiserfs_de_head*) ; 
 int deh_offset (struct reiserfs_de_head*) ; 
 int deh_state (struct reiserfs_de_head*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void sprintf_de_head(char *buf, struct reiserfs_de_head *deh)
{
	if (deh)
		sprintf(buf,
			"[offset=%d dir_id=%d objectid=%d location=%d state=%04x]",
			deh_offset(deh), deh_dir_id(deh), deh_objectid(deh),
			deh_location(deh), deh_state(deh));
	else
		sprintf(buf, "[NULL]");

}