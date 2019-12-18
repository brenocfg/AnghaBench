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
struct nouveau_mem_exec_func {int /*<<< orphan*/  dev; } ;
struct nouveau_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 

__attribute__((used)) static void
mclk_refresh_self(struct nouveau_mem_exec_func *exec, bool enable)
{
	struct nouveau_device *device = nouveau_dev(exec->dev);
	nv_wr32(device, 0x1002dc, enable ? 0x00000001 : 0x00000000);
}