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
 unsigned int* BCH18_6_CODES ; 
 int qr_hamming_dist (unsigned int,unsigned int,int) ; 

__attribute__((used)) static int bch18_6_correct(unsigned *_y){
  unsigned x;
  unsigned y;
  int      nerrs;
  y=*_y;
  /*Check the easy case first: see if the data bits were uncorrupted.*/
  x=y>>12;
  if(x>=7&&x<=40){
    nerrs=qr_hamming_dist(y,BCH18_6_CODES[x-7],4);
    if(nerrs<4){
      *_y=BCH18_6_CODES[x-7];
      return nerrs;
    }
  }
  /*Exhaustive search is faster than field operations in GF(19).*/
  for(x=0;x<34;x++)if(x+7!=y>>12){
    nerrs=qr_hamming_dist(y,BCH18_6_CODES[x],4);
    if(nerrs<4){
      *_y=BCH18_6_CODES[x];
      return nerrs;
    }
  }
  return -1;
}