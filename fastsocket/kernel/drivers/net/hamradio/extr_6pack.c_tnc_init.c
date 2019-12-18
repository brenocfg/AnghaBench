#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct sixpack {TYPE_3__ resync_t; TYPE_2__* tty; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* write ) (TYPE_2__*,unsigned char*,int) ;} ;

/* Variables and functions */
 scalar_t__ SIXP_RESYNC_TIMEOUT ; 
 int /*<<< orphan*/  TNC_UNSYNC_STARTUP ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  resync_tnc ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  tnc_set_sync_state (struct sixpack*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tnc_init(struct sixpack *sp)
{
	unsigned char inbyte = 0xe8;

	tnc_set_sync_state(sp, TNC_UNSYNC_STARTUP);

	sp->tty->ops->write(sp->tty, &inbyte, 1);

	del_timer(&sp->resync_t);
	sp->resync_t.data = (unsigned long) sp;
	sp->resync_t.function = resync_tnc;
	sp->resync_t.expires = jiffies + SIXP_RESYNC_TIMEOUT;
	add_timer(&sp->resync_t);

	return 0;
}