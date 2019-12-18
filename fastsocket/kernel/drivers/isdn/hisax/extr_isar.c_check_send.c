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
typedef  int u_char ;
struct IsdnCardState {int dummy; } ;
struct BCState {scalar_t__ mode; } ;

/* Variables and functions */
 int BSTAT_RDM1 ; 
 int BSTAT_RDM2 ; 
 struct BCState* sel_bcs_isar (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  send_frames (struct BCState*) ; 

__attribute__((used)) static inline void
check_send(struct IsdnCardState *cs, u_char rdm)
{
	struct BCState *bcs;
	
	if (rdm & BSTAT_RDM1) {
		if ((bcs = sel_bcs_isar(cs, 1))) {
			if (bcs->mode) {
				send_frames(bcs);
			}
		}
	}
	if (rdm & BSTAT_RDM2) {
		if ((bcs = sel_bcs_isar(cs, 2))) {
			if (bcs->mode) {
				send_frames(bcs);
			}
		}
	}
	
}