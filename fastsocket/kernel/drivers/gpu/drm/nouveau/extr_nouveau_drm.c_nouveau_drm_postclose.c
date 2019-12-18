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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 int /*<<< orphan*/  nouveau_cli_destroy (struct nouveau_cli*) ; 

__attribute__((used)) static void
nouveau_drm_postclose(struct drm_device *dev, struct drm_file *fpriv)
{
	struct nouveau_cli *cli = nouveau_cli(fpriv);
	nouveau_cli_destroy(cli);
}