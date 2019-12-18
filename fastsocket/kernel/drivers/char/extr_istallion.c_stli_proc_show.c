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
struct stliport {int dummy; } ;
struct stlibrd {scalar_t__ state; unsigned int nrports; struct stliport** ports; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 unsigned int STL_MAXPORTS ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stlibrd** stli_brds ; 
 int /*<<< orphan*/  stli_drvtitle ; 
 int /*<<< orphan*/  stli_drvversion ; 
 unsigned int stli_nrbrds ; 
 int /*<<< orphan*/  stli_portinfo (struct seq_file*,struct stlibrd*,struct stliport*,unsigned int) ; 

__attribute__((used)) static int stli_proc_show(struct seq_file *m, void *v)
{
	struct stlibrd *brdp;
	struct stliport *portp;
	unsigned int brdnr, portnr, totalport;

	totalport = 0;

	seq_printf(m, "%s: version %s\n", stli_drvtitle, stli_drvversion);

/*
 *	We scan through for each board, panel and port. The offset is
 *	calculated on the fly, and irrelevant ports are skipped.
 */
	for (brdnr = 0; (brdnr < stli_nrbrds); brdnr++) {
		brdp = stli_brds[brdnr];
		if (brdp == NULL)
			continue;
		if (brdp->state == 0)
			continue;

		totalport = brdnr * STL_MAXPORTS;
		for (portnr = 0; (portnr < brdp->nrports); portnr++,
		    totalport++) {
			portp = brdp->ports[portnr];
			if (portp == NULL)
				continue;
			stli_portinfo(m, brdp, portp, totalport);
		}
	}
	return 0;
}