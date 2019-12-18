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
struct pvr2_context_stream {struct pvr2_channel* user; } ;
struct pvr2_channel {int /*<<< orphan*/  mc_head; struct pvr2_context_stream* stream; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  pvr2_channel_disclaim_stream (struct pvr2_channel*) ; 
 int /*<<< orphan*/  pvr2_context_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_context_exit (int /*<<< orphan*/ ) ; 

int pvr2_channel_claim_stream(struct pvr2_channel *cp,
			      struct pvr2_context_stream *sp)
{
	int code = 0;
	pvr2_context_enter(cp->mc_head); do {
		if (sp == cp->stream) break;
		if (sp && sp->user) {
			code = -EBUSY;
			break;
		}
		pvr2_channel_disclaim_stream(cp);
		if (!sp) break;
		sp->user = cp;
		cp->stream = sp;
	} while (0); pvr2_context_exit(cp->mc_head);
	return code;
}