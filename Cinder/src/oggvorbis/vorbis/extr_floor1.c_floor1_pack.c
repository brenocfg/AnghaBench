#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* postlist; int partitions; int* partitionclass; int* class_dim; int* class_subs; int* class_book; int** class_subbook; int mult; } ;
typedef  TYPE_1__ vorbis_info_floor1 ;
typedef  int /*<<< orphan*/  vorbis_info_floor ;
typedef  int /*<<< orphan*/  oggpack_buffer ;

/* Variables and functions */
 int ilog2 (int) ; 
 int /*<<< orphan*/  oggpack_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void floor1_pack (vorbis_info_floor *i,oggpack_buffer *opb){
  vorbis_info_floor1 *info=(vorbis_info_floor1 *)i;
  int j,k;
  int count=0;
  int rangebits;
  int maxposit=info->postlist[1];
  int maxclass=-1;

  /* save out partitions */
  oggpack_write(opb,info->partitions,5); /* only 0 to 31 legal */
  for(j=0;j<info->partitions;j++){
    oggpack_write(opb,info->partitionclass[j],4); /* only 0 to 15 legal */
    if(maxclass<info->partitionclass[j])maxclass=info->partitionclass[j];
  }

  /* save out partition classes */
  for(j=0;j<maxclass+1;j++){
    oggpack_write(opb,info->class_dim[j]-1,3); /* 1 to 8 */
    oggpack_write(opb,info->class_subs[j],2); /* 0 to 3 */
    if(info->class_subs[j])oggpack_write(opb,info->class_book[j],8);
    for(k=0;k<(1<<info->class_subs[j]);k++)
      oggpack_write(opb,info->class_subbook[j][k]+1,8);
  }

  /* save out the post list */
  oggpack_write(opb,info->mult-1,2);     /* only 1,2,3,4 legal now */
  oggpack_write(opb,ilog2(maxposit),4);
  rangebits=ilog2(maxposit);

  for(j=0,k=0;j<info->partitions;j++){
    count+=info->class_dim[info->partitionclass[j]];
    for(;k<count;k++)
      oggpack_write(opb,info->postlist[k+2],rangebits);
  }
}