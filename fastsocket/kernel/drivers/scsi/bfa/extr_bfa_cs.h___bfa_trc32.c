#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct TYPE_3__ {int /*<<< orphan*/  u32; } ;
struct TYPE_4__ {TYPE_1__ u32; } ;
struct bfa_trc_s {int /*<<< orphan*/  timestamp; TYPE_2__ data; void* line; void* fileno; } ;
struct bfa_trc_mod_s {int tail; int head; scalar_t__ stopped; struct bfa_trc_s* trc; } ;

/* Variables and functions */
 int BFA_TRC_MAX ; 
 int /*<<< orphan*/  BFA_TRC_TS (struct bfa_trc_mod_s*) ; 

__attribute__((used)) static inline void
__bfa_trc32(struct bfa_trc_mod_s *trcm, int fileno, int line, u32 data)
{
	int		tail = trcm->tail;
	struct bfa_trc_s *trc = &trcm->trc[tail];

	if (trcm->stopped)
		return;

	trc->fileno = (u16) fileno;
	trc->line = (u16) line;
	trc->data.u32.u32 = data;
	trc->timestamp = BFA_TRC_TS(trcm);

	trcm->tail = (trcm->tail + 1) & (BFA_TRC_MAX - 1);
	if (trcm->tail == trcm->head)
		trcm->head = (trcm->head + 1) & (BFA_TRC_MAX - 1);
}