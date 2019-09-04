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
struct tty {int /*<<< orphan*/  t_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct ptmx_ioctl {TYPE_1__ pt_selw; TYPE_1__ pt_selr; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TSA_PTC_READ (struct tty*) ; 
 int /*<<< orphan*/  TSA_PTC_WRITE (struct tty*) ; 
 struct ptmx_ioctl* pty_get_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptcwakeup(struct tty *tp, int flag)
{
	struct ptmx_ioctl *pti = pty_get_ioctl(tp->t_dev, 0, NULL);
	if (pti == NULL)
		return;

	if (flag & FREAD) {
		selwakeup(&pti->pt_selr);
		wakeup(TSA_PTC_READ(tp));
		KNOTE(&pti->pt_selr.si_note, 1);
	}
	if (flag & FWRITE) {
		selwakeup(&pti->pt_selw);
		wakeup(TSA_PTC_WRITE(tp));
		KNOTE(&pti->pt_selw.si_note, 1);
	}
}