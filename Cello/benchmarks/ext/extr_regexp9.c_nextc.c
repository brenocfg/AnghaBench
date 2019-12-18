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
typedef  char Rune ;

/* Variables and functions */
 scalar_t__ chartorune (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprp ; 
 int lexdone ; 

__attribute__((used)) static	int
nextc(Rune *rp)
{
	if(lexdone){
		*rp = 0;
		return 1;
	}
	exprp += chartorune(rp, exprp);
	if(*rp == '\\'){
		exprp += chartorune(rp, exprp);
		return 1;
	}
	if(*rp == 0)
		lexdone = 1;
	return 0;
}