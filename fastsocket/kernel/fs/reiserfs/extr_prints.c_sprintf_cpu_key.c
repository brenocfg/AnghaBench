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
struct TYPE_2__ {int k_dir_id; int k_objectid; } ;
struct cpu_key {TYPE_1__ on_disk_key; } ;

/* Variables and functions */
 char* cpu_type (struct cpu_key*) ; 
 char* reiserfs_cpu_offset (struct cpu_key*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void sprintf_cpu_key(char *buf, struct cpu_key *key)
{
	if (key)
		sprintf(buf, "[%d %d %s %s]", key->on_disk_key.k_dir_id,
			key->on_disk_key.k_objectid, reiserfs_cpu_offset(key),
			cpu_type(key));
	else
		sprintf(buf, "[NULL]");
}