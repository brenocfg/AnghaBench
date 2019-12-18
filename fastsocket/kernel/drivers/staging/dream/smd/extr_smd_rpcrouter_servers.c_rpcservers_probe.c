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
struct task_struct {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 struct task_struct* endpoint ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct task_struct* msm_rpc_open () ; 
 int /*<<< orphan*/  rpc_server_register_all () ; 
 int rpc_servers_active ; 
 int /*<<< orphan*/  rpc_servers_thread ; 

__attribute__((used)) static int rpcservers_probe(struct platform_device *pdev)
{
	struct task_struct *server_thread;

	endpoint = msm_rpc_open();
	if (IS_ERR(endpoint))
		return PTR_ERR(endpoint);

	/* we're online -- register any servers installed beforehand */
	rpc_servers_active = 1;
	rpc_server_register_all();

	/* start the kernel thread */
	server_thread = kthread_run(rpc_servers_thread, NULL, "krpcserversd");
	if (IS_ERR(server_thread))
		return PTR_ERR(server_thread);

	return 0;
}