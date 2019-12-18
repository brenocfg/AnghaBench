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
struct uvc_video_chain {int /*<<< orphan*/  dev; int /*<<< orphan*/  entities; struct uvc_entity* selector; } ;
struct uvc_entity {int* baSourceID; int bNrInPins; int /*<<< orphan*/  chain; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVC_ENTITY_IS_ITERM (struct uvc_entity*) ; 
 int /*<<< orphan*/  UVC_ENTITY_IS_OTERM (struct uvc_entity*) ; 
 int UVC_ENTITY_TYPE (struct uvc_entity*) ; 
#define  UVC_ITT_CAMERA 137 
#define  UVC_ITT_MEDIA_TRANSPORT_INPUT 136 
#define  UVC_ITT_VENDOR_SPECIFIC 135 
#define  UVC_OTT_DISPLAY 134 
#define  UVC_OTT_MEDIA_TRANSPORT_OUTPUT 133 
#define  UVC_OTT_VENDOR_SPECIFIC 132 
 int /*<<< orphan*/  UVC_TRACE_DESCR ; 
 int UVC_TRACE_PROBE ; 
#define  UVC_TT_STREAMING 131 
#define  UVC_VC_EXTENSION_UNIT 130 
#define  UVC_VC_PROCESSING_UNIT 129 
#define  UVC_VC_SELECTOR_UNIT 128 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct uvc_entity* uvc_entity_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uvc_scan_chain_forward (struct uvc_video_chain*,struct uvc_entity*,struct uvc_entity*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int,...) ; 
 int uvc_trace_param ; 

__attribute__((used)) static int uvc_scan_chain_backward(struct uvc_video_chain *chain,
	struct uvc_entity **_entity)
{
	struct uvc_entity *entity = *_entity;
	struct uvc_entity *term;
	int id = -EINVAL, i;

	switch (UVC_ENTITY_TYPE(entity)) {
	case UVC_VC_EXTENSION_UNIT:
	case UVC_VC_PROCESSING_UNIT:
		id = entity->baSourceID[0];
		break;

	case UVC_VC_SELECTOR_UNIT:
		/* Single-input selector units are ignored. */
		if (entity->bNrInPins == 1) {
			id = entity->baSourceID[0];
			break;
		}

		if (uvc_trace_param & UVC_TRACE_PROBE)
			printk(" <- IT");

		chain->selector = entity;
		for (i = 0; i < entity->bNrInPins; ++i) {
			id = entity->baSourceID[i];
			term = uvc_entity_by_id(chain->dev, id);
			if (term == NULL || !UVC_ENTITY_IS_ITERM(term)) {
				uvc_trace(UVC_TRACE_DESCR, "Selector unit %d "
					"input %d isn't connected to an "
					"input terminal\n", entity->id, i);
				return -1;
			}

			if (uvc_trace_param & UVC_TRACE_PROBE)
				printk(" %d", term->id);

			list_add_tail(&term->chain, &chain->entities);
			uvc_scan_chain_forward(chain, term, entity);
		}

		if (uvc_trace_param & UVC_TRACE_PROBE)
			printk("\n");

		id = 0;
		break;

	case UVC_ITT_VENDOR_SPECIFIC:
	case UVC_ITT_CAMERA:
	case UVC_ITT_MEDIA_TRANSPORT_INPUT:
	case UVC_OTT_VENDOR_SPECIFIC:
	case UVC_OTT_DISPLAY:
	case UVC_OTT_MEDIA_TRANSPORT_OUTPUT:
	case UVC_TT_STREAMING:
		id = UVC_ENTITY_IS_OTERM(entity) ? entity->baSourceID[0] : 0;
		break;
	}

	if (id <= 0) {
		*_entity = NULL;
		return id;
	}

	entity = uvc_entity_by_id(chain->dev, id);
	if (entity == NULL) {
		uvc_trace(UVC_TRACE_DESCR, "Found reference to "
			"unknown entity %d.\n", id);
		return -EINVAL;
	}

	*_entity = entity;
	return 0;
}