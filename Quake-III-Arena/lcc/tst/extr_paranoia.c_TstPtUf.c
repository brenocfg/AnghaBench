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
 int /*<<< orphan*/  BadCond (size_t,char*) ; 
 size_t Defect ; 
 scalar_t__* ErrCnt ; 
 int FABS (double) ; 
 int N ; 
 double One ; 
 int /*<<< orphan*/  Pause () ; 
 double Q9 ; 
 int Radix ; 
 double Random1 ; 
 double Random2 ; 
 size_t Serious ; 
 double Two ; 
 int U2 ; 
 double V9 ; 
 double Z ; 
 double Zero ; 
 int /*<<< orphan*/  ovfl_buf ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 scalar_t__ sigfpe ; 
 scalar_t__ sigsave ; 

TstPtUf()
{
	N = 0;
	if (Z != Zero) {
		printf("Since comparison denies Z = 0, evaluating ");
		printf("(Z + Z) / Z should be safe.\n");
		sigsave = sigfpe;
		if (setjmp(ovfl_buf)) goto very_serious;
		Q9 = (Z + Z) / Z;
		printf("What the machine gets for (Z + Z) / Z is  %.17e .\n",
			Q9);
		if (FABS(Q9 - Two) < Radix * U2) {
			printf("This is O.K., provided Over/Underflow");
			printf(" has NOT just been signaled.\n");
			}
		else {
			if ((Q9 < One) || (Q9 > Two)) {
very_serious:
				N = 1;
				ErrCnt [Serious] = ErrCnt [Serious] + 1;
				printf("This is a VERY SERIOUS DEFECT!\n");
				}
			else {
				N = 1;
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				printf("This is a DEFECT!\n");
				}
			}
		sigsave = 0;
		V9 = Z * One;
		Random1 = V9;
		V9 = One * Z;
		Random2 = V9;
		V9 = Z / One;
		if ((Z == Random1) && (Z == Random2) && (Z == V9)) {
			if (N > 0) Pause();
			}
		else {
			N = 1;
			BadCond(Defect, "What prints as Z = ");
			printf("%.17e\n\tcompares different from  ", Z);
			if (Z != Random1) printf("Z * 1 = %.17e ", Random1);
			if (! ((Z == Random2)
				|| (Random2 == Random1)))
				printf("1 * Z == %g\n", Random2);
			if (! (Z == V9)) printf("Z / 1 = %.17e\n", V9);
			if (Random2 != Random1) {
				ErrCnt [Defect] = ErrCnt [Defect] + 1;
				BadCond(Defect, "Multiplication does not commute!\n");
				printf("\tComparison alleges that 1 * Z = %.17e\n",
					Random2);
				printf("\tdiffers from Z * 1 = %.17e\n", Random1);
				}
			Pause();
			}
		}
	}