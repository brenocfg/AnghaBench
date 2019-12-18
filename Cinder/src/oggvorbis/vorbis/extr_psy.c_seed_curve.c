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
 float const EHMER_OFFSET ; 
 scalar_t__ P_LEVELS ; 
 float P_LEVEL_0 ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,scalar_t__) ; 

__attribute__((used)) static void seed_curve(float *seed,
                       const float **curves,
                       float amp,
                       int oc, int n,
                       int linesper,float dBoffset){
  int i,post1;
  int seedptr;
  const float *posts,*curve;

  int choice=(int)((amp+dBoffset-P_LEVEL_0)*.1f);
  choice=max(choice,0);
  choice=min(choice,P_LEVELS-1);
  posts=curves[choice];
  curve=posts+2;
  post1=(int)posts[1];
  seedptr=oc+(posts[0]-EHMER_OFFSET)*linesper-(linesper>>1);

  for(i=posts[0];i<post1;i++){
    if(seedptr>0){
      float lin=amp+curve[i];
      if(seed[seedptr]<lin)seed[seedptr]=lin;
    }
    seedptr+=linesper;
    if(seedptr>=n)break;
  }
}