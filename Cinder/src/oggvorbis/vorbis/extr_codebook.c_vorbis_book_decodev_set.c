#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_4__ {scalar_t__ used_entries; float* valuelist; int dim; } ;
typedef  TYPE_1__ codebook ;

/* Variables and functions */
 int decode_packed_entry_number (TYPE_1__*,int /*<<< orphan*/ *) ; 

long vorbis_book_decodev_set(codebook *book,float *a,oggpack_buffer *b,int n){
  if(book->used_entries>0){
    int i,j,entry;
    float *t;

    for(i=0;i<n;){
      entry = decode_packed_entry_number(book,b);
      if(entry==-1)return(-1);
      t     = book->valuelist+entry*book->dim;
      for (j=0;i<n && j<book->dim;){
        a[i++]=t[j++];
      }
    }
  }else{
    int i;

    for(i=0;i<n;){
      a[i++]=0.f;
    }
  }
  return(0);
}