#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uwb_rc_evt_beacon {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct uwb_rc {TYPE_1__ uwb_beca; } ;
struct uwb_beca_e {unsigned long ts_jiffies; int /*<<< orphan*/  node; int /*<<< orphan*/ * uwb_dev; } ;
struct uwb_beacon_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct uwb_beca_e* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_beca_e_init (struct uwb_beca_e*) ; 

__attribute__((used)) static
struct uwb_beca_e *__uwb_beca_add(struct uwb_rc *rc,
				  struct uwb_rc_evt_beacon *be,
				  struct uwb_beacon_frame *bf,
				  unsigned long ts_jiffies)
{
	struct uwb_beca_e *bce;

	bce = kzalloc(sizeof(*bce), GFP_KERNEL);
	if (bce == NULL)
		return NULL;
	uwb_beca_e_init(bce);
	bce->ts_jiffies = ts_jiffies;
	bce->uwb_dev = NULL;
	list_add(&bce->node, &rc->uwb_beca.list);
	return bce;
}