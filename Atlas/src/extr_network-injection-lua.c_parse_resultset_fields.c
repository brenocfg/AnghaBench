#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rows_chunk_head; scalar_t__ fields; TYPE_1__* result_queue; } ;
typedef  TYPE_2__ proxy_resultset_t ;
struct TYPE_8__ {int /*<<< orphan*/  next; } ;
struct TYPE_6__ {int /*<<< orphan*/  head; } ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 scalar_t__ network_mysqld_proto_fielddefs_new () ; 
 TYPE_3__* network_mysqld_proto_get_fielddefs (int /*<<< orphan*/ ,scalar_t__) ; 

int parse_resultset_fields(proxy_resultset_t *res) {
	GList *chunk;

	g_return_val_if_fail(res->result_queue != NULL, -1);
    
	if (res->fields) return 0;

   	/* parse the fields */
	res->fields = network_mysqld_proto_fielddefs_new();
    
	if (!res->fields) return -1;
    
	chunk = network_mysqld_proto_get_fielddefs(res->result_queue->head, res->fields);
    
	/* no result-set found */
	if (!chunk) return -1;
    
	/* skip the end-of-fields chunk */
	res->rows_chunk_head = chunk->next;
    
	return 0;
}