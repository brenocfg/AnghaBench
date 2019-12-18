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
struct TYPE_4__ {scalar_t__ used_entries; int binarypoint; int* valuelist; long dim; } ;
typedef  TYPE_1__ codebook ;

/* Variables and functions */
 long decode_packed_entry_number (TYPE_1__*,int /*<<< orphan*/ *) ; 

long vorbis_book_decodevv_add(codebook *book,ogg_int32_t **a,\
			      long offset,int ch,
			      oggpack_buffer *b,int n,int point){
  if(book->used_entries>0){
    long i,j,entry;
    int chptr=0;
    int shift=point-book->binarypoint;
    int m=offset+n;
    if(shift>=0){
      
      for(i=offset;i<m;){
	entry = decode_packed_entry_number(book,b);
	if(entry==-1)return(-1);
	{
	  const ogg_int32_t *t = book->valuelist+entry*book->dim;
	  for (j=0;i<m && j<book->dim;j++){
	    a[chptr++][i]+=t[j]>>shift;
	    if(chptr==ch){
	      chptr=0;
	      i++;
	    }
	  }
	}
      }
    }else{
      
      for(i=offset;i<m;){
	entry = decode_packed_entry_number(book,b);
	if(entry==-1)return(-1);
	{
	  const ogg_int32_t *t = book->valuelist+entry*book->dim;
	  for (j=0;i<m && j<book->dim;j++){
	    a[chptr++][i]+=t[j]<<-shift;
	    if(chptr==ch){
	      chptr=0;
	      i++;
	    }
	  }
	}
      }
    }
  }
  return(0);
}