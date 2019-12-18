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
struct nouveau_therm_priv {int /*<<< orphan*/  mode; int /*<<< orphan*/  suspend; } ;
struct nouveau_therm {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_THERM_CTRL_NONE ; 
 int nouveau_subdev_fini (int /*<<< orphan*/ *,int) ; 

int
_nouveau_therm_fini(struct nouveau_object *object, bool suspend)
{
	struct nouveau_therm *therm = (void *)object;
	struct nouveau_therm_priv *priv = (void *)therm;

	if (suspend) {
		priv->suspend = priv->mode;
		priv->mode = NOUVEAU_THERM_CTRL_NONE;
	}

	return nouveau_subdev_fini(&therm->base, suspend);
}