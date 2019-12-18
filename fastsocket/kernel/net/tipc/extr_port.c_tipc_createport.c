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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tipc_named_msg_event ;
typedef  int /*<<< orphan*/  tipc_named_msg_err_event ;
typedef  int /*<<< orphan*/  tipc_msg_event ;
typedef  int /*<<< orphan*/  tipc_msg_err_event ;
typedef  int /*<<< orphan*/  tipc_continue_event ;
typedef  int /*<<< orphan*/  tipc_conn_shutdown_event ;
typedef  int /*<<< orphan*/  tipc_conn_msg_event ;
struct user_port {int /*<<< orphan*/  uport_list; int /*<<< orphan*/  continue_event_cb; int /*<<< orphan*/  conn_msg_cb; int /*<<< orphan*/  named_msg_cb; int /*<<< orphan*/  msg_cb; int /*<<< orphan*/  conn_err_cb; int /*<<< orphan*/  named_err_cb; int /*<<< orphan*/  err_cb; int /*<<< orphan*/  ref; void* usr_handle; int /*<<< orphan*/  user_ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;
struct port {TYPE_1__ publ; struct user_port* user_port; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct user_port*) ; 
 struct user_port* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_dispatcher ; 
 int /*<<< orphan*/  port_wakeup ; 
 scalar_t__ tipc_createport_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 
 int /*<<< orphan*/  tipc_reg_add_port (struct user_port*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int tipc_createport(u32 user_ref,
		    void *usr_handle,
		    unsigned int importance,
		    tipc_msg_err_event error_cb,
		    tipc_named_msg_err_event named_error_cb,
		    tipc_conn_shutdown_event conn_error_cb,
		    tipc_msg_event msg_cb,
		    tipc_named_msg_event named_msg_cb,
		    tipc_conn_msg_event conn_msg_cb,
		    tipc_continue_event continue_event_cb,/* May be zero */
		    u32 *portref)
{
	struct user_port *up_ptr;
	struct port *p_ptr;

	up_ptr = kmalloc(sizeof(*up_ptr), GFP_ATOMIC);
	if (!up_ptr) {
		warn("Port creation failed, no memory\n");
		return -ENOMEM;
	}
	p_ptr = (struct port *)tipc_createport_raw(NULL, port_dispatcher,
						   port_wakeup, importance);
	if (!p_ptr) {
		kfree(up_ptr);
		return -ENOMEM;
	}

	p_ptr->user_port = up_ptr;
	up_ptr->user_ref = user_ref;
	up_ptr->usr_handle = usr_handle;
	up_ptr->ref = p_ptr->publ.ref;
	up_ptr->err_cb = error_cb;
	up_ptr->named_err_cb = named_error_cb;
	up_ptr->conn_err_cb = conn_error_cb;
	up_ptr->msg_cb = msg_cb;
	up_ptr->named_msg_cb = named_msg_cb;
	up_ptr->conn_msg_cb = conn_msg_cb;
	up_ptr->continue_event_cb = continue_event_cb;
	INIT_LIST_HEAD(&up_ptr->uport_list);
	tipc_reg_add_port(up_ptr);
	*portref = p_ptr->publ.ref;
	tipc_port_unlock(p_ptr);
	return 0;
}