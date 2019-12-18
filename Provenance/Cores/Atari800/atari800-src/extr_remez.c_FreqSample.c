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
 int POSITIVE ; 
 int Pi ; 
 int Pi2 ; 
 double cos (double) ; 
 double sin (double) ; 

__attribute__((used)) static void FreqSample(int N, const double A[], double h[], int symm)
{
	int n, k;
	double x, val, M;

	M = (N - 1.0) / 2.0;
	if (symm == POSITIVE) {
		if (N % 2) {
			for (n = 0; n < N; n++) {
				val = A[0];
				x = Pi2 * (n - M) / N;
				for (k = 1; k <= M; k++)
					val += 2.0 * A[k] * cos(x * k);
				h[n] = val / N;
			}
		}
		else {
			for (n = 0; n < N; n++) {
				val = A[0];
				x = Pi2 * (n - M)/N;
				for (k = 1; k <= (N / 2 - 1); k++)
					val += 2.0 * A[k] * cos(x * k);
				h[n] = val / N;
			}
		}
	}
	else {
		if (N % 2) {
			for (n = 0; n < N; n++) {
				val = 0;
				x = Pi2 * (n - M) / N;
				for (k = 1; k <= M; k++)
					val += 2.0 * A[k] * sin(x * k);
				h[n] = val / N;
			}
		}
		else {
			for (n = 0; n < N; n++) {
				val = A[N / 2] * sin(Pi * (n - M));
				x = Pi2 * (n - M) / N;
				for (k = 1; k <= (N / 2 - 1); k++)
					val += 2.0 * A[k] * sin(x * k);
				h[n] = val / N;
			}
		}
	}
}