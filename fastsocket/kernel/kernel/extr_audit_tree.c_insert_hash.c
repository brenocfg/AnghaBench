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
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inode; } ;
struct audit_chunk {int /*<<< orphan*/  hash; TYPE_1__ watch; } ;

/* Variables and functions */
 struct list_head* chunk_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void insert_hash(struct audit_chunk *chunk)
{
	struct list_head *list = chunk_hash(chunk->watch.inode);
	list_add_rcu(&chunk->hash, list);
}