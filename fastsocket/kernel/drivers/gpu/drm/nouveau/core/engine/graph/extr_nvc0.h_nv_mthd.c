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
typedef  int u32 ;
struct nvc0_graph_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 

__attribute__((used)) static inline void
nv_mthd(struct nvc0_graph_priv *priv, u32 class, u32 mthd, u32 data)
{
	nv_wr32(priv, 0x40448c, data);
	nv_wr32(priv, 0x404488, 0x80000000 | (mthd << 14) | class);
}