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
struct nv04_fence_priv {int dummy; } ;
struct nouveau_drm {struct nv04_fence_priv* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nv04_fence_priv*) ; 

__attribute__((used)) static void
nv04_fence_destroy(struct nouveau_drm *drm)
{
	struct nv04_fence_priv *priv = drm->fence;
	drm->fence = NULL;
	kfree(priv);
}