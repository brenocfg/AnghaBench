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
struct nv50_graph_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_error (struct nv50_graph_priv*,char*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void nouveau_pgraph_vstatus_print(struct nv50_graph_priv *priv, int r,
		const char *const units[], u32 status)
{
	int i;

	nv_error(priv, "PGRAPH_VSTATUS%d: 0x%08x", r, status);

	for (i = 0; units[i] && status; i++) {
		if ((status & 7) == 1)
			pr_cont(" %s", units[i]);
		status >>= 3;
	}
	if (status)
		pr_cont(" (invalid: 0x%x)", status);
	pr_cont("\n");
}