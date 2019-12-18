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
struct nouveau_cli {int /*<<< orphan*/  mutex; } ;
struct nouveau_abi16 {scalar_t__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
nouveau_abi16_put(struct nouveau_abi16 *abi16, int ret)
{
	struct nouveau_cli *cli = (void *)abi16->client;
	mutex_unlock(&cli->mutex);
	return ret;
}