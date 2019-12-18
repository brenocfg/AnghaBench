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
 float C0 ; 
 float C1 ; 
 float C2 ; 
 float C3 ; 

void daub4(float b[], unsigned long n, int isign)
{
	float wksp[4097];
	float	*a=b-1;						// numerical recipies so a[1] = b[0]

	unsigned long nh,nh1,i,j;

	if (n < 4) return;

	nh1=(nh=n >> 1)+1;
	if (isign >= 0) {
		for (i=1,j=1;j<=n-3;j+=2,i++) {
			wksp[i]	   = C0*a[j]+C1*a[j+1]+C2*a[j+2]+C3*a[j+3];
			wksp[i+nh] = C3*a[j]-C2*a[j+1]+C1*a[j+2]-C0*a[j+3];
		}
		wksp[i   ] = C0*a[n-1]+C1*a[n]+C2*a[1]+C3*a[2];
		wksp[i+nh] = C3*a[n-1]-C2*a[n]+C1*a[1]-C0*a[2];
	} else {
		wksp[1] = C2*a[nh]+C1*a[n]+C0*a[1]+C3*a[nh1];
		wksp[2] = C3*a[nh]-C0*a[n]+C1*a[1]-C2*a[nh1];
		for (i=1,j=3;i<nh;i++) {
			wksp[j++] = C2*a[i]+C1*a[i+nh]+C0*a[i+1]+C3*a[i+nh1];
			wksp[j++] = C3*a[i]-C0*a[i+nh]+C1*a[i+1]-C2*a[i+nh1];
		}
	}
	for (i=1;i<=n;i++) {
		a[i]=wksp[i];
	}
}