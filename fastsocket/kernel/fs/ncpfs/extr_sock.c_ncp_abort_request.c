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
struct TYPE_2__ {int /*<<< orphan*/  creq_mutex; } ;
struct ncp_server {TYPE_1__ rcv; } ;
struct ncp_request_reply {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ncp_abort_request (struct ncp_server*,struct ncp_request_reply*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ncp_abort_request(struct ncp_server *server, struct ncp_request_reply *req, int err)
{
	mutex_lock(&server->rcv.creq_mutex);
	__ncp_abort_request(server, req, err);
	mutex_unlock(&server->rcv.creq_mutex);
}