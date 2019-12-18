#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_8__ {unsigned int count; int /*<<< orphan*/  type; int /*<<< orphan*/  target_lp; } ;
struct TYPE_9__ {TYPE_3__ alloc; } ;
struct TYPE_6__ {int /*<<< orphan*/  xSubtypeData; } ;
struct TYPE_7__ {int xSubtype; TYPE_1__ x; scalar_t__ xCorrelationToken; } ;
struct TYPE_10__ {TYPE_4__ data; TYPE_2__ hp_lp_event; } ;
struct pending_event {int /*<<< orphan*/  (* hdlr ) (void*,int) ;TYPE_5__ event; } ;
typedef  int /*<<< orphan*/  (* MFCompleteHandler ) (void*,int) ;
typedef  int /*<<< orphan*/  HvLpIndex ;
typedef  int /*<<< orphan*/  HvLpEvent_Type ;

/* Variables and functions */
 int ENOMEM ; 
 struct pending_event* new_pending_event () ; 
 int signal_event (struct pending_event*) ; 
 int /*<<< orphan*/  stub1 (void*,int) ; 
 int /*<<< orphan*/  subtype_data (char,float,char,char) ; 

void mf_deallocate_lp_events(HvLpIndex target_lp, HvLpEvent_Type type,
		unsigned count, MFCompleteHandler hdlr, void *user_token)
{
	struct pending_event *ev = new_pending_event();
	int rc;

	if (ev == NULL)
		rc = -ENOMEM;
	else {
		ev->event.hp_lp_event.xSubtype = 5;
		ev->event.hp_lp_event.xCorrelationToken = (u64)user_token;
		ev->event.hp_lp_event.x.xSubtypeData =
			subtype_data('M', 'F', 'M', 'D');
		ev->event.data.alloc.target_lp = target_lp;
		ev->event.data.alloc.type = type;
		ev->event.data.alloc.count = count;
		ev->hdlr = hdlr;
		rc = signal_event(ev);
	}
	if ((rc != 0) && (hdlr != NULL))
		(*hdlr)(user_token, rc);
}