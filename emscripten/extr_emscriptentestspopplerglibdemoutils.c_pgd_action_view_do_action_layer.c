#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {int action; TYPE_2__* layers; } ;
typedef  int /*<<< orphan*/  PopplerLayer ;
typedef  TYPE_1__ PopplerActionLayer ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
#define  POPPLER_ACTION_LAYER_OFF 130 
#define  POPPLER_ACTION_LAYER_ON 129 
#define  POPPLER_ACTION_LAYER_TOGGLE 128 
 TYPE_2__* g_list_next (TYPE_2__*) ; 
 int /*<<< orphan*/  poppler_layer_hide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_layer_is_visible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_layer_show (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_action_view_do_action_layer (GtkWidget *button,
				 GList     *state_list)
{
	GList *l, *m;

	for (l = state_list; l; l = g_list_next (l)) {
		PopplerActionLayer *action_layer = (PopplerActionLayer *)l->data;

		for (m = action_layer->layers; m; m = g_list_next (m)) {
			PopplerLayer *layer = (PopplerLayer *)m->data;

			switch (action_layer->action) {
			case POPPLER_ACTION_LAYER_ON:
				poppler_layer_show (layer);
				break;
			case POPPLER_ACTION_LAYER_OFF:
				poppler_layer_hide (layer);
				break;
			case POPPLER_ACTION_LAYER_TOGGLE:
				if (poppler_layer_is_visible (layer))
					poppler_layer_hide (layer);
				else
					poppler_layer_show (layer);
				break;
			}
		}
	}
}