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
struct TYPE_4__ {scalar_t__ used_entries; int dim; int binarypoint; int* valuelist; } ;
typedef  TYPE_1__ codebook ;

/* Variables and functions */
 scalar_t__ alloca (int) ; 
 long decode_packed_entry_number (TYPE_1__*,int /*<<< orphan*/ *) ; 

long vorbis_book_decodevs_add(codebook *book,ogg_int32_t *a,
			      oggpack_buffer *b,int n,int point){
  if(book->used_entries>0){  
    int step=n/book->dim;
    long *entry = (long *)alloca(sizeof(*entry)*step);
    ogg_int32_t **t = (ogg_int32_t **)alloca(sizeof(*t)*step);
    int i,j,o;
    int shift=point-book->binarypoint;
    
    if(shift>=0){
      for (i = 0; i < step; i++) {
	entry[i]=decode_packed_entry_number(book,b);
	if(entry[i]==-1)return(-1);
	t[i] = book->valuelist+entry[i]*book->dim;
      }
      for(i=0,o=0;i<book->dim;i++,o+=step)
	for (j=0;o+j<n && j<step;j++)
	  a[o+j]+=t[j][i]>>shift;
    }else{
      for (i = 0; i < step; i++) {
	entry[i]=decode_packed_entry_number(book,b);
	if(entry[i]==-1)return(-1);
	t[i] = book->valuelist+entry[i]*book->dim;
      }
      for(i=0,o=0;i<book->dim;i++,o+=step)
	for (j=0;o+j<n && j<step;j++)
	  a[o+j]+=t[j][i]<<-shift;
    }
  }
  return(0);
}