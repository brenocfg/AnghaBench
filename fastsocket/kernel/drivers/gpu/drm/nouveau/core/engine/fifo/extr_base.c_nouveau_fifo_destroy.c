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
struct nouveau_fifo {int /*<<< orphan*/  base; int /*<<< orphan*/  uevent; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_engine_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_event_destroy (int /*<<< orphan*/ *) ; 

void
nouveau_fifo_destroy(struct nouveau_fifo *priv)
{
	kfree(priv->channel);
	nouveau_event_destroy(&priv->uevent);
	nouveau_engine_destroy(&priv->base);
}