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
struct crypto_queue {int dummy; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 struct crypto_async_request* __crypto_dequeue_request (struct crypto_queue*,int /*<<< orphan*/ ) ; 

struct crypto_async_request *crypto_dequeue_request(struct crypto_queue *queue)
{
	return __crypto_dequeue_request(queue, 0);
}