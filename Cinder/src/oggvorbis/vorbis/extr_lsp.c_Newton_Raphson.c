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
 double* alloca (int) ; 

__attribute__((used)) static int Newton_Raphson(float *a,int ord,float *r){
  int i, k, count=0;
  double error=1.f;
  double *root=alloca(ord*sizeof(*root));

  for(i=0; i<ord;i++) root[i] = r[i];

  while(error>1e-20){
    error=0;

    for(i=0; i<ord; i++) { /* Update each point. */
      double pp=0.,delta;
      double rooti=root[i];
      double p=a[ord];
      for(k=ord-1; k>= 0; k--) {

        pp= pp* rooti + p;
        p = p * rooti + a[k];
      }

      delta = p/pp;
      root[i] -= delta;
      error+= delta*delta;
    }

    if(count>40)return(-1);

    count++;
  }

  /* Replaced the original bubble sort with a real sort.  With your
     help, we can eliminate the bubble sort in our lifetime. --Monty */

  for(i=0; i<ord;i++) r[i] = root[i];
  return(0);
}