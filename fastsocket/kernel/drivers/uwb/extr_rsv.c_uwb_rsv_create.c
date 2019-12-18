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
typedef  int /*<<< orphan*/  uwb_rsv_cb_f ;
struct uwb_rsv {void* pal_priv; int /*<<< orphan*/  callback; } ;
struct uwb_rc {int dummy; } ;

/* Variables and functions */
 struct uwb_rsv* uwb_rsv_alloc (struct uwb_rc*) ; 

struct uwb_rsv *uwb_rsv_create(struct uwb_rc *rc, uwb_rsv_cb_f cb, void *pal_priv)
{
	struct uwb_rsv *rsv;

	rsv = uwb_rsv_alloc(rc);
	if (!rsv)
		return NULL;

	rsv->callback = cb;
	rsv->pal_priv = pal_priv;

	return rsv;
}