#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {TYPE_4__ nodeName; int /*<<< orphan*/  parentID; scalar_t__ reserved; } ;
struct TYPE_6__ {TYPE_1__ thread; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ hfsplus_cat_entry ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsplus_asc2uni (struct super_block*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfsplus_fill_cat_thread(struct super_block *sb,
				   hfsplus_cat_entry *entry, int type,
				   u32 parentid, struct qstr *str)
{
	entry->type = cpu_to_be16(type);
	entry->thread.reserved = 0;
	entry->thread.parentID = cpu_to_be32(parentid);
	hfsplus_asc2uni(sb, &entry->thread.nodeName, str->name, str->len);
	return 10 + be16_to_cpu(entry->thread.nodeName.length) * 2;
}