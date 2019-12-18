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
struct nouveau_therm_priv {struct nouveau_fan* fan; } ;
struct nouveau_therm {int dummy; } ;
struct nouveau_fan {char* type; int /*<<< orphan*/  set; int /*<<< orphan*/  get; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nouveau_fan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fannil_get ; 
 int /*<<< orphan*/  nouveau_fannil_set ; 

int
nouveau_fannil_create(struct nouveau_therm *therm)
{
	struct nouveau_therm_priv *tpriv = (void *)therm;
	struct nouveau_fan *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	tpriv->fan = priv;
	if (!priv)
		return -ENOMEM;

	priv->type = "none / external";
	priv->get = nouveau_fannil_get;
	priv->set = nouveau_fannil_set;
	return 0;
}