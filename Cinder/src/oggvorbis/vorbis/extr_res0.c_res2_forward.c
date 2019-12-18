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
typedef  int /*<<< orphan*/  vorbis_look_residue ;
struct TYPE_4__ {int pcmend; } ;
typedef  TYPE_1__ vorbis_block ;
typedef  int /*<<< orphan*/  oggpack_buffer ;

/* Variables and functions */
 int _01forward (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int**,int,long**,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  _encodepart ; 
 int* _vorbis_block_alloc (TYPE_1__*,int) ; 

int res2_forward(oggpack_buffer *opb,
                 vorbis_block *vb,vorbis_look_residue *vl,
                 int **in,int *nonzero,int ch, long **partword,int submap){
  long i,j,k,n=vb->pcmend/2,used=0;

  /* don't duplicate the code; use a working vector hack for now and
     reshape ourselves into a single channel res1 */
  /* ugly; reallocs for each coupling pass :-( */
  int *work=_vorbis_block_alloc(vb,ch*n*sizeof(*work));
  for(i=0;i<ch;i++){
    int *pcm=in[i];
    if(nonzero[i])used++;
    for(j=0,k=i;j<n;j++,k+=ch)
      work[k]=pcm[j];
  }

  if(used){
#ifdef TRAIN_RES
    return _01forward(opb,vl,&work,1,partword,_encodepart,submap);
#else
    (void)submap;
    return _01forward(opb,vl,&work,1,partword,_encodepart);
#endif
  }else{
    return(0);
  }
}