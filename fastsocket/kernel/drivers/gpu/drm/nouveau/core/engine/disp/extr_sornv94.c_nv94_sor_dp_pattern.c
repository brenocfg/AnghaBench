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
typedef  scalar_t__ u32 ;
struct nv50_disp_priv {int dummy; } ;
struct nouveau_disp {int dummy; } ;
struct dcb_output {int dummy; } ;

/* Variables and functions */
 scalar_t__ nv94_sor_loff (struct dcb_output*) ; 
 int /*<<< orphan*/  nv_mask (struct nv50_disp_priv*,scalar_t__ const,int,int) ; 

__attribute__((used)) static int
nv94_sor_dp_pattern(struct nouveau_disp *disp, struct dcb_output *outp,
		    int head, int pattern)
{
	struct nv50_disp_priv *priv = (void *)disp;
	const u32 loff = nv94_sor_loff(outp);
	nv_mask(priv, 0x61c10c + loff, 0x0f000000, pattern << 24);
	return 0;
}