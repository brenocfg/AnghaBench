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

/* Variables and functions */
 int _01inverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_book_decodev_add ; 

int res1_inverse(vorbis_block *vb,vorbis_look_residue *vl,
                 float **in,int *nonzero,int ch){
  int i,used=0;
  for(i=0;i<ch;i++)
    if(nonzero[i])
      in[used++]=in[i];
  if(used)
    return(_01inverse(vb,vl,in,used,vorbis_book_decodev_add));
  else
    return(0);
}