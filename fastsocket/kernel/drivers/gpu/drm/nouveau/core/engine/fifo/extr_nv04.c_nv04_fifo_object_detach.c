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
struct nv04_fifo_priv {int /*<<< orphan*/  ramht; } ;
struct nouveau_object {scalar_t__ engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_ramht_remove (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* nv_subdev (struct nv04_fifo_priv*) ; 

void
nv04_fifo_object_detach(struct nouveau_object *parent, int cookie)
{
	struct nv04_fifo_priv *priv = (void *)parent->engine;
	mutex_lock(&nv_subdev(priv)->mutex);
	nouveau_ramht_remove(priv->ramht, cookie);
	mutex_unlock(&nv_subdev(priv)->mutex);
}