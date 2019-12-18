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
 float cos (float) ; 
 float sin (float) ; 

__attribute__((used)) static void drfti1(int n, float *wa, int *ifac){
  static int ntryh[4] = { 4,2,3,5 };
  static float tpi = 6.28318530717958648f;
  float arg,argh,argld,fi;
  int ntry=0,i,j=-1;
  int k1, l1, l2, ib;
  int ld, ii, ip, is, nq, nr;
  int ido, ipm, nfm1;
  int nl=n;
  int nf=0;

 L101:
  j++;
  if (j < 4)
    ntry=ntryh[j];
  else
    ntry+=2;

 L104:
  nq=nl/ntry;
  nr=nl-ntry*nq;
  if (nr!=0) goto L101;

  nf++;
  ifac[nf+1]=ntry;
  nl=nq;
  if(ntry!=2)goto L107;
  if(nf==1)goto L107;

  for (i=1;i<nf;i++){
    ib=nf-i+1;
    ifac[ib+1]=ifac[ib];
  }
  ifac[2] = 2;

 L107:
  if(nl!=1)goto L104;
  ifac[0]=n;
  ifac[1]=nf;
  argh=tpi/n;
  is=0;
  nfm1=nf-1;
  l1=1;

  if(nfm1==0)return;

  for (k1=0;k1<nfm1;k1++){
    ip=ifac[k1+2];
    ld=0;
    l2=l1*ip;
    ido=n/l2;
    ipm=ip-1;

    for (j=0;j<ipm;j++){
      ld+=l1;
      i=is;
      argld=(float)ld*argh;
      fi=0.f;
      for (ii=2;ii<ido;ii+=2){
        fi+=1.f;
        arg=fi*argld;
        wa[i++]=cos(arg);
        wa[i++]=sin(arg);
      }
      is+=ido;
    }
    l1=l2;
  }
}