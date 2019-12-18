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
 int /*<<< orphan*/  dradb2 (int,int,float*,float*,float*) ; 
 int /*<<< orphan*/  dradb3 (int,int,float*,float*,float*,float*) ; 
 int /*<<< orphan*/  dradb4 (int,int,float*,float*,float*,float*,float*) ; 
 int /*<<< orphan*/  dradbg (int,int,int,int,float*,float*,float*,float*,float*,float*) ; 

__attribute__((used)) static void drftb1(int n, float *c, float *ch, float *wa, int *ifac){
  int i,k1,l1,l2;
  int na;
  int nf,ip,iw,ix2,ix3,ido,idl1;

  nf=ifac[1];
  na=0;
  l1=1;
  iw=1;

  for(k1=0;k1<nf;k1++){
    ip=ifac[k1 + 2];
    l2=ip*l1;
    ido=n/l2;
    idl1=ido*l1;
    if(ip!=4)goto L103;
    ix2=iw+ido;
    ix3=ix2+ido;

    if(na!=0)
      dradb4(ido,l1,ch,c,wa+iw-1,wa+ix2-1,wa+ix3-1);
    else
      dradb4(ido,l1,c,ch,wa+iw-1,wa+ix2-1,wa+ix3-1);
    na=1-na;
    goto L115;

  L103:
    if(ip!=2)goto L106;

    if(na!=0)
      dradb2(ido,l1,ch,c,wa+iw-1);
    else
      dradb2(ido,l1,c,ch,wa+iw-1);
    na=1-na;
    goto L115;

  L106:
    if(ip!=3)goto L109;

    ix2=iw+ido;
    if(na!=0)
      dradb3(ido,l1,ch,c,wa+iw-1,wa+ix2-1);
    else
      dradb3(ido,l1,c,ch,wa+iw-1,wa+ix2-1);
    na=1-na;
    goto L115;

  L109:
/*    The radix five case can be translated later..... */
/*    if(ip!=5)goto L112;

    ix2=iw+ido;
    ix3=ix2+ido;
    ix4=ix3+ido;
    if(na!=0)
      dradb5(ido,l1,ch,c,wa+iw-1,wa+ix2-1,wa+ix3-1,wa+ix4-1);
    else
      dradb5(ido,l1,c,ch,wa+iw-1,wa+ix2-1,wa+ix3-1,wa+ix4-1);
    na=1-na;
    goto L115;

  L112:*/
    if(na!=0)
      dradbg(ido,ip,l1,idl1,ch,ch,ch,c,c,wa+iw-1);
    else
      dradbg(ido,ip,l1,idl1,c,c,c,ch,ch,wa+iw-1);
    if(ido==1)na=1-na;

  L115:
    l1=l2;
    iw+=(ip-1)*ido;
  }

  if(na==0)return;

  for(i=0;i<n;i++)c[i]=ch[i];
}