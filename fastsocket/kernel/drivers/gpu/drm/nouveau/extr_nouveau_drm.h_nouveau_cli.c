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
struct nouveau_cli {int dummy; } ;
struct drm_file {struct nouveau_cli* driver_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct nouveau_cli *
nouveau_cli(struct drm_file *fpriv)
{
	return fpriv ? fpriv->driver_priv : NULL;
}