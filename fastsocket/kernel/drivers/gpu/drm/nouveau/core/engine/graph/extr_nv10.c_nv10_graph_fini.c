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
struct nv10_graph_priv {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nouveau_graph_fini (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nv10_graph_fini(struct nouveau_object *object, bool suspend)
{
	struct nv10_graph_priv *priv = (void *)object;
	return nouveau_graph_fini(&priv->base, suspend);
}