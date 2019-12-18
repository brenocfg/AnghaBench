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
struct reiserfs_key {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 char* le_offset (struct reiserfs_key*) ; 
 char* le_type (struct reiserfs_key*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void sprintf_le_key(char *buf, struct reiserfs_key *key)
{
	if (key)
		sprintf(buf, "[%d %d %s %s]", le32_to_cpu(key->k_dir_id),
			le32_to_cpu(key->k_objectid), le_offset(key),
			le_type(key));
	else
		sprintf(buf, "[NULL]");
}