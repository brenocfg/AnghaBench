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
struct aic7xxx_host {int dummy; } ;

/* Variables and functions */
 int CLRATNO ; 
 int CLRBRKADRINT ; 
 int CLRBUSFREE ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRPARERR ; 
 int CLRPHASECHG ; 
 int CLRREQINIT ; 
 int CLRSCSIINT ; 
 int CLRSCSIPERR ; 
 int CLRSCSIRSTI ; 
 int CLRSELDI ; 
 int CLRSELDO ; 
 int CLRSELINGO ; 
 int CLRSELTIMEO ; 
 int CLRSEQINT ; 
 int /*<<< orphan*/  CLRSINT0 ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aic7xxx_clear_intstat(struct aic7xxx_host *p)
{
  /* Clear any interrupt conditions this may have caused. */
  aic_outb(p, CLRSELDO | CLRSELDI | CLRSELINGO, CLRSINT0);
  aic_outb(p, CLRSELTIMEO | CLRATNO | CLRSCSIRSTI | CLRBUSFREE | CLRSCSIPERR |
       CLRPHASECHG | CLRREQINIT, CLRSINT1);
  aic_outb(p, CLRSCSIINT | CLRSEQINT | CLRBRKADRINT | CLRPARERR, CLRINT);
}