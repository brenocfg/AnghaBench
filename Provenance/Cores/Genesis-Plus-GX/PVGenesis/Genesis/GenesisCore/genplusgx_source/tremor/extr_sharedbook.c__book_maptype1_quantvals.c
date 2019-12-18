#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int entries; int dim; } ;
typedef  TYPE_1__ static_codebook ;

/* Variables and functions */
 int _ilog (int) ; 

long _book_maptype1_quantvals(const static_codebook *b){
  /* get us a starting hint, we'll polish it below */
  int bits=_ilog(b->entries);
  int vals=b->entries>>((bits-1)*(b->dim-1)/b->dim);

  while(1){
    long acc=1;
    long acc1=1;
    int i;
    for(i=0;i<b->dim;i++){
      acc*=vals;
      acc1*=vals+1;
    }
    if(acc<=b->entries && acc1>b->entries){
      return(vals);
    }else{
      if(acc>b->entries){
	vals--;
      }else{
	vals++;
      }
    }
  }
}