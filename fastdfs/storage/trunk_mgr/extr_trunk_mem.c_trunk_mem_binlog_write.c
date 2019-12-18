#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_6__ {TYPE_1__ file; } ;
typedef  TYPE_2__ FDFSTrunkFullInfo ;

/* Variables and functions */
 char const TRUNK_OP_TYPE_ADD_SPACE ; 
 char const TRUNK_OP_TYPE_DEL_SPACE ; 
 int /*<<< orphan*/  g_trunk_total_free_space ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int trunk_binlog_write (int const,char const,TYPE_2__ const*) ; 
 int /*<<< orphan*/  trunk_file_lock ; 

__attribute__((used)) static int trunk_mem_binlog_write(const int timestamp, const char op_type, \
		const FDFSTrunkFullInfo *pTrunk)
{
	pthread_mutex_lock(&trunk_file_lock);
	if (op_type == TRUNK_OP_TYPE_ADD_SPACE)
	{
		g_trunk_total_free_space += pTrunk->file.size;
	}
	else if (op_type == TRUNK_OP_TYPE_DEL_SPACE)
	{
		g_trunk_total_free_space -= pTrunk->file.size;
	}
	pthread_mutex_unlock(&trunk_file_lock);

	return trunk_binlog_write(timestamp, op_type, pTrunk);
}