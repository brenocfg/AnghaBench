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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int nv04_graph_mthd_bind_class (struct nouveau_object*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_graph_set_ctx_val (struct nouveau_object*,int,int) ; 

__attribute__((used)) static int
nv04_graph_mthd_bind_surf_color(struct nouveau_object *object, u32 mthd,
				void *args, u32 size)
{
	switch (nv04_graph_mthd_bind_class(object, args, size)) {
	case 0x30:
		nv04_graph_set_ctx_val(object, 0x02000000, 0);
		return 0;
	case 0x5a:
		nv04_graph_set_ctx_val(object, 0x02000000, 0x02000000);
		return 0;
	}
	return 1;
}