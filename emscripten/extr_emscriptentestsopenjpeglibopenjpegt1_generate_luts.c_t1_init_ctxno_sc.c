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
 int T1_CTXNO_SC ; 
 int T1_SGN_E ; 
 int T1_SGN_N ; 
 int T1_SGN_S ; 
 int T1_SGN_W ; 
 int T1_SIG_E ; 
 int T1_SIG_N ; 
 int T1_SIG_S ; 
 int T1_SIG_W ; 
 int int_min (int,int) ; 

__attribute__((used)) static int t1_init_ctxno_sc(int f) {
	int hc, vc, n;
	n = 0;

	hc = int_min(((f & (T1_SIG_E | T1_SGN_E)) ==
				T1_SIG_E) + ((f & (T1_SIG_W | T1_SGN_W)) == T1_SIG_W),
			1) - int_min(((f & (T1_SIG_E | T1_SGN_E)) ==
					(T1_SIG_E | T1_SGN_E)) +
				((f & (T1_SIG_W | T1_SGN_W)) ==
				 (T1_SIG_W | T1_SGN_W)), 1);

	vc = int_min(((f & (T1_SIG_N | T1_SGN_N)) ==
				T1_SIG_N) + ((f & (T1_SIG_S | T1_SGN_S)) == T1_SIG_S),
			1) - int_min(((f & (T1_SIG_N | T1_SGN_N)) ==
					(T1_SIG_N | T1_SGN_N)) +
				((f & (T1_SIG_S | T1_SGN_S)) ==
				 (T1_SIG_S | T1_SGN_S)), 1);

	if (hc < 0) {
		hc = -hc;
		vc = -vc;
	}
	if (!hc) {
		if (vc == -1)
			n = 1;
		else if (!vc)
			n = 0;
		else
			n = 1;
	} else if (hc == 1) {
		if (vc == -1)
			n = 2;
		else if (!vc)
			n = 3;
		else
			n = 4;
	}

	return (T1_CTXNO_SC + n);
}