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
struct crypto_async_request {int dummy; } ;
struct cryptd_queue {int /*<<< orphan*/  cpu_queue; } ;
struct cryptd_cpu_queue {int /*<<< orphan*/  work; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  kcrypto_wq ; 
 struct cryptd_cpu_queue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cryptd_enqueue_request(struct cryptd_queue *queue,
				  struct crypto_async_request *request)
{
	int cpu, err;
	struct cryptd_cpu_queue *cpu_queue;

	cpu = get_cpu();
	cpu_queue = per_cpu_ptr(queue->cpu_queue, cpu);
	err = crypto_enqueue_request(&cpu_queue->queue, request);
	queue_work_on(cpu, kcrypto_wq, &cpu_queue->work);
	put_cpu();

	return err;
}