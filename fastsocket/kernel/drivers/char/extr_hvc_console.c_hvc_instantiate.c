#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct hvc_struct {int /*<<< orphan*/  kref; } ;
struct hv_ops {int dummy; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int MAX_NR_HVC_CONSOLES ; 
 struct hv_ops const** cons_ops ; 
 int /*<<< orphan*/  destroy_hvc_struct ; 
 TYPE_1__ hvc_con_driver ; 
 struct hvc_struct* hvc_get_by_index (int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int last_hvc ; 
 int /*<<< orphan*/  register_console (TYPE_1__*) ; 
 int* vtermnos ; 

int hvc_instantiate(uint32_t vtermno, int index, const struct hv_ops *ops)
{
	struct hvc_struct *hp;

	if (index < 0 || index >= MAX_NR_HVC_CONSOLES)
		return -1;

	if (vtermnos[index] != -1)
		return -1;

	/* make sure no no tty has been registered in this index */
	hp = hvc_get_by_index(index);
	if (hp) {
		kref_put(&hp->kref, destroy_hvc_struct);
		return -1;
	}

	vtermnos[index] = vtermno;
	cons_ops[index] = ops;

	/* reserve all indices up to and including this index */
	if (last_hvc < index)
		last_hvc = index;

	/* if this index is what the user requested, then register
	 * now (setup won't fail at this point).  It's ok to just
	 * call register again if previously .setup failed.
	 */
	if (index == hvc_con_driver.index)
		register_console(&hvc_con_driver);

	return 0;
}