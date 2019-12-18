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
typedef  int ogg_int32_t ;
struct TYPE_4__ {scalar_t__ used_entries; int binarypoint; int* valuelist; int dim; } ;
typedef  TYPE_1__ codebook ;

/* Variables and functions */
 int decode_packed_entry_number (TYPE_1__*,int /*<<< orphan*/ *) ; 

long vorbis_book_decodev_add(codebook *book,ogg_int32_t *a,
			     oggpack_buffer *b,int n,int point){
  if(book->used_entries>0){
    int i,j,entry;
    ogg_int32_t *t;
    int shift=point-book->binarypoint;
    
    if(shift>=0){
      for(i=0;i<n;){
	entry = decode_packed_entry_number(book,b);
	if(entry==-1)return(-1);
	t     = book->valuelist+entry*book->dim;
	for (j=0;i<n && j<book->dim;)
	  a[i++]+=t[j++]>>shift;
      }
    }else{
      for(i=0;i<n;){
	entry = decode_packed_entry_number(book,b);
	if(entry==-1)return(-1);
	t     = book->valuelist+entry*book->dim;
	for (j=0;i<n && j<book->dim;)
	  a[i++]+=t[j++]<<-shift;
      }
    }
  }
  return(0);
}