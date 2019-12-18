#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int train_seq; int /*<<< orphan*/  frames; TYPE_2__* info; } ;
typedef  TYPE_1__ vorbis_look_residue0 ;
typedef  int /*<<< orphan*/  vorbis_look_residue ;
struct TYPE_4__ {int grouping; int partitions; int end; long begin; int* classmetric1; int* classmetric2; } ;
typedef  TYPE_2__ vorbis_info_residue0 ;
typedef  int /*<<< orphan*/  vorbis_block ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* _vorbis_block_alloc (int /*<<< orphan*/ *,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memset (long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static long **_01class(vorbis_block *vb,vorbis_look_residue *vl,
                       int **in,int ch){
  long i,j,k;
  vorbis_look_residue0 *look=(vorbis_look_residue0 *)vl;
  vorbis_info_residue0 *info=look->info;

  /* move all this setup out later */
  int samples_per_partition=info->grouping;
  int possible_partitions=info->partitions;
  int n=info->end-info->begin;

  int partvals=n/samples_per_partition;
  long **partword=_vorbis_block_alloc(vb,ch*sizeof(*partword));
  float scale=100./samples_per_partition;

  /* we find the partition type for each partition of each
     channel.  We'll go back and do the interleaved encoding in a
     bit.  For now, clarity */

  for(i=0;i<ch;i++){
    partword[i]=_vorbis_block_alloc(vb,n/samples_per_partition*sizeof(*partword[i]));
    memset(partword[i],0,n/samples_per_partition*sizeof(*partword[i]));
  }

  for(i=0;i<partvals;i++){
    int offset=i*samples_per_partition+info->begin;
    for(j=0;j<ch;j++){
      int max=0;
      int ent=0;
      for(k=0;k<samples_per_partition;k++){
        if(abs(in[j][offset+k])>max)max=abs(in[j][offset+k]);
        ent+=abs(in[j][offset+k]);
      }
      ent*=scale;

      for(k=0;k<possible_partitions-1;k++)
        if(max<=info->classmetric1[k] &&
           (info->classmetric2[k]<0 || ent<info->classmetric2[k]))
          break;

      partword[j][i]=k;
    }
  }

#ifdef TRAIN_RESAUX
  {
    FILE *of;
    char buffer[80];

    for(i=0;i<ch;i++){
      sprintf(buffer,"resaux_%d.vqd",look->train_seq);
      of=fopen(buffer,"a");
      for(j=0;j<partvals;j++)
        fprintf(of,"%ld, ",partword[i][j]);
      fprintf(of,"\n");
      fclose(of);
    }
  }
#endif
  look->frames++;

  return(partword);
}