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

__attribute__((used)) static void dradb4(int ido,int l1,float *cc,float *ch,float *wa1,
                          float *wa2,float *wa3){
  static float sqrt2=1.414213562373095f;
  int i,k,t0,t1,t2,t3,t4,t5,t6,t7,t8;
  float ci2,ci3,ci4,cr2,cr3,cr4,ti1,ti2,ti3,ti4,tr1,tr2,tr3,tr4;
  t0=l1*ido;

  t1=0;
  t2=ido<<2;
  t3=0;
  t6=ido<<1;
  for(k=0;k<l1;k++){
    t4=t3+t6;
    t5=t1;
    tr3=cc[t4-1]+cc[t4-1];
    tr4=cc[t4]+cc[t4];
    tr1=cc[t3]-cc[(t4+=t6)-1];
    tr2=cc[t3]+cc[t4-1];
    ch[t5]=tr2+tr3;
    ch[t5+=t0]=tr1-tr4;
    ch[t5+=t0]=tr2-tr3;
    ch[t5+=t0]=tr1+tr4;
    t1+=ido;
    t3+=t2;
  }

  if(ido<2)return;
  if(ido==2)goto L105;

  t1=0;
  for(k=0;k<l1;k++){
    t5=(t4=(t3=(t2=t1<<2)+t6))+t6;
    t7=t1;
    for(i=2;i<ido;i+=2){
      t2+=2;
      t3+=2;
      t4-=2;
      t5-=2;
      t7+=2;
      ti1=cc[t2]+cc[t5];
      ti2=cc[t2]-cc[t5];
      ti3=cc[t3]-cc[t4];
      tr4=cc[t3]+cc[t4];
      tr1=cc[t2-1]-cc[t5-1];
      tr2=cc[t2-1]+cc[t5-1];
      ti4=cc[t3-1]-cc[t4-1];
      tr3=cc[t3-1]+cc[t4-1];
      ch[t7-1]=tr2+tr3;
      cr3=tr2-tr3;
      ch[t7]=ti2+ti3;
      ci3=ti2-ti3;
      cr2=tr1-tr4;
      cr4=tr1+tr4;
      ci2=ti1+ti4;
      ci4=ti1-ti4;

      ch[(t8=t7+t0)-1]=wa1[i-2]*cr2-wa1[i-1]*ci2;
      ch[t8]=wa1[i-2]*ci2+wa1[i-1]*cr2;
      ch[(t8+=t0)-1]=wa2[i-2]*cr3-wa2[i-1]*ci3;
      ch[t8]=wa2[i-2]*ci3+wa2[i-1]*cr3;
      ch[(t8+=t0)-1]=wa3[i-2]*cr4-wa3[i-1]*ci4;
      ch[t8]=wa3[i-2]*ci4+wa3[i-1]*cr4;
    }
    t1+=ido;
  }

  if(ido%2 == 1)return;

 L105:

  t1=ido;
  t2=ido<<2;
  t3=ido-1;
  t4=ido+(ido<<1);
  for(k=0;k<l1;k++){
    t5=t3;
    ti1=cc[t1]+cc[t4];
    ti2=cc[t4]-cc[t1];
    tr1=cc[t1-1]-cc[t4-1];
    tr2=cc[t1-1]+cc[t4-1];
    ch[t5]=tr2+tr2;
    ch[t5+=t0]=sqrt2*(tr1-ti1);
    ch[t5+=t0]=ti2+ti2;
    ch[t5+=t0]=-sqrt2*(tr1+ti1);

    t3+=ido;
    t1+=t2;
    t4+=t2;
  }
}