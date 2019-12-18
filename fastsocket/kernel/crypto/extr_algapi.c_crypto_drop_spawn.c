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
struct crypto_spawn {int /*<<< orphan*/  list; int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_alg_sem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void crypto_drop_spawn(struct crypto_spawn *spawn)
{
	if (!spawn->alg)
		return;

	down_write(&crypto_alg_sem);
	list_del(&spawn->list);
	up_write(&crypto_alg_sem);
}