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
struct stlport {int dummy; } ;
struct stlpanel {unsigned int nrports; struct stlport** ports; } ;
struct stlbrd {unsigned int nrpanels; struct stlpanel** panels; } ;

/* Variables and functions */
 int STL_MAXBRDS ; 
 struct stlbrd** stl_brds ; 

__attribute__((used)) static struct stlport *stl_getport(int brdnr, int panelnr, int portnr)
{
	struct stlbrd	*brdp;
	struct stlpanel	*panelp;

	if (brdnr < 0 || brdnr >= STL_MAXBRDS)
		return NULL;
	brdp = stl_brds[brdnr];
	if (brdp == NULL)
		return NULL;
	if (panelnr < 0 || (unsigned int)panelnr >= brdp->nrpanels)
		return NULL;
	panelp = brdp->panels[panelnr];
	if (panelp == NULL)
		return NULL;
	if (portnr < 0 || (unsigned int)portnr >= panelp->nrports)
		return NULL;
	return panelp->ports[portnr];
}