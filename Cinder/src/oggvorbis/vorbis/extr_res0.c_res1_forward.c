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
typedef  int /*<<< orphan*/  vorbis_look_residue ;
typedef  int /*<<< orphan*/  vorbis_block ;
typedef  int /*<<< orphan*/  oggpack_buffer ;

/* Variables and functions */
 int _01forward (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int**,int,long**,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  _encodepart ; 

int res1_forward(oggpack_buffer *opb,vorbis_block *vb,vorbis_look_residue *vl,
                 int **in,int *nonzero,int ch, long **partword, int submap){
  int i,used=0;
  (void)vb;
  for(i=0;i<ch;i++)
    if(nonzero[i])
      in[used++]=in[i];

  if(used){
#ifdef TRAIN_RES
    return _01forward(opb,vl,in,used,partword,_encodepart,submap);
#else
    (void)submap;
    return _01forward(opb,vl,in,used,partword,_encodepart);
#endif
  }else{
    return(0);
  }
}