#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ c_cc; } ;
struct tty {size_t t_line; int /*<<< orphan*/  t_state; TYPE_1__ t_outq; int /*<<< orphan*/  t_dev; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int /*<<< orphan*/  (* l_start ) (struct tty*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TS_BUSY ; 
 int /*<<< orphan*/  cnputsusr (char*,int) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  kmputc (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  kmtimeout ; 
 TYPE_3__* linesw ; 
 int min (int,int) ; 
 int ndqb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_to_b (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub1 (struct tty*) ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kmoutput(struct tty * tp)
{
	unsigned char	buf[80];	/* buffer; limits output per call */
	unsigned char	*cp;
	int	cc = -1;

	/* While there is data available to be output... */
	while (tp->t_outq.c_cc > 0) {
		cc = ndqb(&tp->t_outq, 0);
		if (cc == 0)
			break;
		/*
		 * attempt to output as many characters as are available,
		 * up to the available transfer buffer size.
		 */
		cc = min(cc, sizeof(buf));
		/* copy the output queue contents to the buffer */
		(void) q_to_b(&tp->t_outq, buf, cc);
		for (cp = buf; cp < &buf[cc]; cp++) {
			/* output the buffer one charatcer at a time */
			*cp = *cp & 0x7f;
		}
		if (cc > 1) {
			cnputsusr((char *)buf, cc);
		} else {
			kmputc(tp->t_dev, *buf);
		}
	}
	/*
	 * XXX This is likely not necessary, as the tty output queue is not
	 * XXX writeable while we hold the tty_lock().
	 */
	if (tp->t_outq.c_cc > 0) {
		timeout(kmtimeout, tp, hz);
	}
	tp->t_state &= ~TS_BUSY;
	/* Start the output processing for the line discipline */
	(*linesw[tp->t_line].l_start) (tp);

	return 0;
}