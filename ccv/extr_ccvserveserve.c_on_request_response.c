#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ response; int /*<<< orphan*/ * connection; } ;
typedef  TYPE_2__ ebb_request_extras ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_3__ ebb_request ;
typedef  int /*<<< orphan*/  ebb_connection ;

/* Variables and functions */
 int /*<<< orphan*/  ebb_connection_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_connection_response_continue ; 

__attribute__((used)) static void on_request_response(void* context)
{
	ebb_request* request = (ebb_request*)context;
	ebb_request_extras* request_extras = (ebb_request_extras*)request->data;
	ebb_connection* connection = request_extras->connection;
	ebb_connection_write(connection, request_extras->response.data, request_extras->response.len, on_connection_response_continue);
}