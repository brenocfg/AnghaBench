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
struct sep_flow_context_t {int message_size_in_bytes; struct sep_driver_add_message_t* message; } ;
struct sep_driver_add_message_t {int message_size_in_bytes; scalar_t__ message_address; int /*<<< orphan*/  flow_id; } ;
struct sep_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SEP_MAX_ADD_MESSAGE_LENGTH_IN_BYTES ; 
 int copy_from_user (struct sep_driver_add_message_t*,void*,int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 struct sep_flow_context_t* sep_find_flow_context (struct sep_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sep_add_flow_tables_message_handler(struct sep_device *sep, unsigned long arg)
{
	int error;
	struct sep_driver_add_message_t command_args;
	struct sep_flow_context_t *flow_context_ptr;

	dbg("SEP Driver:--------> sep_add_flow_tables_message_handler start\n");

	error = copy_from_user(&command_args, (void *) arg, sizeof(struct sep_driver_add_message_t));
	if (error)
		goto end_function;

	/* check input */
	if (command_args.message_size_in_bytes > SEP_MAX_ADD_MESSAGE_LENGTH_IN_BYTES) {
		error = -ENOMEM;
		goto end_function;
	}

	/* find the flow context */
	flow_context_ptr = sep_find_flow_context(sep, command_args.flow_id);
	if (flow_context_ptr == NULL)
		goto end_function;

	/* copy the message into context */
	flow_context_ptr->message_size_in_bytes = command_args.message_size_in_bytes;
	error = copy_from_user(flow_context_ptr->message, (void *) command_args.message_address, command_args.message_size_in_bytes);
end_function:
	dbg("SEP Driver:<-------- sep_add_flow_tables_message_handler end\n");
	return error;
}