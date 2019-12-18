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
struct stliport {int dummy; } ;
struct stlibrd {int state; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int hwid; int signals; scalar_t__ rxoverrun; scalar_t__ rxbreaks; scalar_t__ rxparity; scalar_t__ rxframing; scalar_t__ rxtotal; scalar_t__ txtotal; } ;

/* Variables and functions */
 int BST_STARTED ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 TYPE_1__ stli_comstats ; 
 int stli_portcmdstats (int /*<<< orphan*/ *,struct stliport*) ; 

__attribute__((used)) static void stli_portinfo(struct seq_file *m, struct stlibrd *brdp, struct stliport *portp, int portnr)
{
	char *uart;
	int rc;

	rc = stli_portcmdstats(NULL, portp);

	uart = "UNKNOWN";
	if (brdp->state & BST_STARTED) {
		switch (stli_comstats.hwid) {
		case 0:	uart = "2681"; break;
		case 1:	uart = "SC26198"; break;
		default:uart = "CD1400"; break;
		}
	}
	seq_printf(m, "%d: uart:%s ", portnr, uart);

	if ((brdp->state & BST_STARTED) && (rc >= 0)) {
		char sep;

		seq_printf(m, "tx:%d rx:%d", (int) stli_comstats.txtotal,
			(int) stli_comstats.rxtotal);

		if (stli_comstats.rxframing)
			seq_printf(m, " fe:%d",
				(int) stli_comstats.rxframing);
		if (stli_comstats.rxparity)
			seq_printf(m, " pe:%d",
				(int) stli_comstats.rxparity);
		if (stli_comstats.rxbreaks)
			seq_printf(m, " brk:%d",
				(int) stli_comstats.rxbreaks);
		if (stli_comstats.rxoverrun)
			seq_printf(m, " oe:%d",
				(int) stli_comstats.rxoverrun);

		sep = ' ';
		if (stli_comstats.signals & TIOCM_RTS) {
			seq_printf(m, "%c%s", sep, "RTS");
			sep = '|';
		}
		if (stli_comstats.signals & TIOCM_CTS) {
			seq_printf(m, "%c%s", sep, "CTS");
			sep = '|';
		}
		if (stli_comstats.signals & TIOCM_DTR) {
			seq_printf(m, "%c%s", sep, "DTR");
			sep = '|';
		}
		if (stli_comstats.signals & TIOCM_CD) {
			seq_printf(m, "%c%s", sep, "DCD");
			sep = '|';
		}
		if (stli_comstats.signals & TIOCM_DSR) {
			seq_printf(m, "%c%s", sep, "DSR");
			sep = '|';
		}
	}
	seq_putc(m, '\n');
}