#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {void* backend_type; void* query; void* backend_xmin; void* backend_xid; void* state; void* wait_event; void* wait_event_type; void* state_change; void* query_start; void* xact_start; void* backend_start; void* client_port; void* client_hostname; int /*<<< orphan*/  client_addr; void* application_name; void* usename; void* usesysid; void* process_id; void* databaese_name; void* database_id; void* distributed_transaction_stamp; void* distributed_transaction_number; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ CitusDistStat ;

/* Variables and functions */
 int /*<<< orphan*/  ParseInetFieldFromHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ParseIntFieldFromHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ParseNameFieldFromHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ParseTextFieldFromHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ParseTimestampTzFieldFromHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ParseXIDFieldFromHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReplaceInitiatorNodeIdentifier (int,TYPE_1__*) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static CitusDistStat *
HeapTupleToCitusDistStat(HeapTuple result, TupleDesc rowDescriptor)
{
	CitusDistStat *citusDistStat = (CitusDistStat *) palloc0(sizeof(CitusDistStat));
	int initiator_node_identifier = 0;

	initiator_node_identifier = ParseIntFieldFromHeapTuple(result, rowDescriptor, 1);

	ReplaceInitiatorNodeIdentifier(initiator_node_identifier, citusDistStat);

	citusDistStat->distributed_transaction_number =
		ParseIntFieldFromHeapTuple(result, rowDescriptor, 2);
	citusDistStat->distributed_transaction_stamp =
		ParseTimestampTzFieldFromHeapTuple(result, rowDescriptor, 3);

	/* fields from pg_stat_statement */
	citusDistStat->database_id = ParseIntFieldFromHeapTuple(result, rowDescriptor, 4);
	citusDistStat->databaese_name = ParseNameFieldFromHeapTuple(result, rowDescriptor, 5);
	citusDistStat->process_id = ParseIntFieldFromHeapTuple(result, rowDescriptor, 6);
	citusDistStat->usesysid = ParseIntFieldFromHeapTuple(result, rowDescriptor, 7);
	citusDistStat->usename = ParseNameFieldFromHeapTuple(result, rowDescriptor, 8);
	citusDistStat->application_name =
		ParseTextFieldFromHeapTuple(result, rowDescriptor, 9);
	citusDistStat->client_addr = ParseInetFieldFromHeapTuple(result, rowDescriptor, 10);
	citusDistStat->client_hostname =
		ParseTextFieldFromHeapTuple(result, rowDescriptor, 11);
	citusDistStat->client_port = ParseIntFieldFromHeapTuple(result, rowDescriptor, 12);
	citusDistStat->backend_start =
		ParseTimestampTzFieldFromHeapTuple(result, rowDescriptor, 13);
	citusDistStat->xact_start =
		ParseTimestampTzFieldFromHeapTuple(result, rowDescriptor, 14);
	citusDistStat->query_start =
		ParseTimestampTzFieldFromHeapTuple(result, rowDescriptor, 15);
	citusDistStat->state_change =
		ParseTimestampTzFieldFromHeapTuple(result, rowDescriptor, 16);
	citusDistStat->wait_event_type =
		ParseTextFieldFromHeapTuple(result, rowDescriptor, 17);
	citusDistStat->wait_event = ParseTextFieldFromHeapTuple(result, rowDescriptor, 18);
	citusDistStat->state = ParseTextFieldFromHeapTuple(result, rowDescriptor, 19);
	citusDistStat->backend_xid = ParseXIDFieldFromHeapTuple(result, rowDescriptor, 20);
	citusDistStat->backend_xmin = ParseXIDFieldFromHeapTuple(result, rowDescriptor, 21);
	citusDistStat->query = ParseTextFieldFromHeapTuple(result, rowDescriptor, 22);
	citusDistStat->backend_type = ParseTextFieldFromHeapTuple(result, rowDescriptor, 23);

	return citusDistStat;
}