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
struct nv50_disp_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exec_script (struct nv50_disp_priv*,int,int) ; 

__attribute__((used)) static void
nvd0_disp_intr_unk2_0(struct nv50_disp_priv *priv, int head)
{
	exec_script(priv, head, 2);
}