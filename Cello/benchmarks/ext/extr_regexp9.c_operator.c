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

/* Variables and functions */
 int CAT ; 
 scalar_t__ FALSE ; 
 int LBRA ; 
 scalar_t__ NSUBEXP ; 
 int PLUS ; 
 int QUEST ; 
 int RBRA ; 
 int STAR ; 
 scalar_t__ TRUE ; 
 scalar_t__ cursubid ; 
 int /*<<< orphan*/  evaluntil (int) ; 
 scalar_t__ lastwasand ; 
 scalar_t__ nbra ; 
 int /*<<< orphan*/  pushator (int) ; 
 int /*<<< orphan*/  rcerror (char*) ; 

__attribute__((used)) static	void
operator(int t)
{
	if(t==RBRA && --nbra<0)
		rcerror("unmatched right paren");
	if(t==LBRA){
		if(++cursubid >= NSUBEXP)
			rcerror ("too many subexpressions");
		nbra++;
		if(lastwasand)
			operator(CAT);
	} else
		evaluntil(t);
	if(t != RBRA)
		pushator(t);
	lastwasand = FALSE;
	if(t==STAR || t==QUEST || t==PLUS || t==RBRA)
		lastwasand = TRUE;	/* these look like operands */
}