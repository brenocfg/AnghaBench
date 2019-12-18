#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ebb_request ;
struct TYPE_3__ {int /*<<< orphan*/ * (* new_request ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ ebb_connection ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_1__*) ; 

__attribute__((used)) static ebb_request* 
new_request_wrapper(void *data)
{
  ebb_connection *connection = data;
  if(connection->new_request)
    return connection->new_request(connection);
  return NULL;
}