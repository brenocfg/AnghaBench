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
struct stlpanel {unsigned int iobase; int /*<<< orphan*/  (* isr ) (struct stlpanel*,unsigned int) ;} ;
struct stlbrd {int /*<<< orphan*/  iostatus; struct stlpanel** panels; } ;

/* Variables and functions */
 int EIO_INTRPEND ; 
 int /*<<< orphan*/  brd_lock ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct stlpanel*,unsigned int) ; 

__attribute__((used)) static int stl_eiointr(struct stlbrd *brdp)
{
	struct stlpanel	*panelp;
	unsigned int	iobase;
	int		handled = 0;

	spin_lock(&brd_lock);
	panelp = brdp->panels[0];
	iobase = panelp->iobase;
	while (inb(brdp->iostatus) & EIO_INTRPEND) {
		handled = 1;
		(* panelp->isr)(panelp, iobase);
	}
	spin_unlock(&brd_lock);
	return handled;
}