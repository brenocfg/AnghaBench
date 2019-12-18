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
typedef  int ogg_uint32_t ;
typedef  int ogg_int32_t ;

/* Variables and functions */
 int COS_LOOKUP_I_SHIFT ; 
 int COS_LOOKUP_I_SZ ; 
 int* MLOOP_1 ; 
 int* MLOOP_2 ; 
 int* MLOOP_3 ; 
 int MULT31_SHIFT15 (int,int) ; 
 int MULT32 (int,int) ; 
 scalar_t__ alloca (int) ; 
 int labs (int) ; 
 int /*<<< orphan*/  lsp_loop_asm (int*,int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  lsp_norm_asm (int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int vorbis_coslook_i (int) ; 
 int vorbis_fromdBlook_i (int) ; 
 int vorbis_invsqlook_i (int,int) ; 

void vorbis_lsp_to_curve(ogg_int32_t *curve,int *map,int n,int ln,
			 ogg_int32_t *lsp,int m,
			 ogg_int32_t amp,
			 ogg_int32_t ampoffset,
			 ogg_int32_t *icos){

  /* 0 <= m < 256 */

  /* set up for using all int later */
  int i;
  int ampoffseti=ampoffset*4096;
  int ampi=amp;
  ogg_int32_t *ilsp=(ogg_int32_t *)alloca(m*sizeof(*ilsp));
  /* lsp is in 8.24, range 0 to PI; coslook wants it in .16 0 to 1*/
  for(i=0;i<m;i++){
#ifndef _LOW_ACCURACY_
    ogg_int32_t val=MULT32(lsp[i],0x517cc2);
#else
    ogg_int32_t val=((lsp[i]>>10)*0x517d)>>14;
#endif

    /* safeguard against a malicious stream */
    if(val<0 || (val>>COS_LOOKUP_I_SHIFT)>=COS_LOOKUP_I_SZ){
      memset(curve,0,sizeof(*curve)*n);
      return;
    }

    ilsp[i]=vorbis_coslook_i(val);
  }

  i=0;
  while(i<n){
    int j,k=map[i];
    ogg_uint32_t pi=46341; /* 2**-.5 in 0.16 */
    ogg_uint32_t qi=46341;
    ogg_int32_t qexp=0,shift;
    ogg_int32_t wi=icos[k];

#ifdef _V_LSP_MATH_ASM
    lsp_loop_asm(&qi,&pi,&qexp,ilsp,wi,m);

    pi=((pi*pi)>>16);
    qi=((qi*qi)>>16);
    
    if(m&1){
      qexp= qexp*2-28*((m+1)>>1)+m;	     
      pi*=(1<<14)-((wi*wi)>>14);
      qi+=pi>>14;     
    }else{
      qexp= qexp*2-13*m;
      
      pi*=(1<<14)-wi;
      qi*=(1<<14)+wi;
      
      qi=(qi+pi)>>14;
    }
    
    if(qi&0xffff0000){ /* checks for 1.xxxxxxxxxxxxxxxx */
      qi>>=1; qexp++; 
    }else
      lsp_norm_asm(&qi,&qexp);

#else

    j=1;
    if(m>1){
      qi*=labs(ilsp[0]-wi);
      pi*=labs(ilsp[1]-wi);

      for(j+=2;j<m;j+=2){
        if(!(shift=MLOOP_1[(pi|qi)>>25]))
          if(!(shift=MLOOP_2[(pi|qi)>>19]))
            shift=MLOOP_3[(pi|qi)>>16];
        qi=(qi>>shift)*labs(ilsp[j-1]-wi);
        pi=(pi>>shift)*labs(ilsp[j]-wi);
        qexp+=shift;
      }
    }
    if(!(shift=MLOOP_1[(pi|qi)>>25]))
      if(!(shift=MLOOP_2[(pi|qi)>>19]))
	shift=MLOOP_3[(pi|qi)>>16];

    /* pi,qi normalized collectively, both tracked using qexp */

    if(m&1){
      /* odd order filter; slightly assymetric */
      /* the last coefficient */
      qi=(qi>>shift)*labs(ilsp[j-1]-wi);
      pi=(pi>>shift)<<14;
      qexp+=shift;

      if(!(shift=MLOOP_1[(pi|qi)>>25]))
	if(!(shift=MLOOP_2[(pi|qi)>>19]))
	  shift=MLOOP_3[(pi|qi)>>16];
      
      pi>>=shift;
      qi>>=shift;
      qexp+=shift-14*((m+1)>>1);

      pi=((pi*pi)>>16);
      qi=((qi*qi)>>16);
      qexp=qexp*2+m;

      pi*=(1<<14)-((wi*wi)>>14);
      qi+=pi>>14;

    }else{
      /* even order filter; still symmetric */

      /* p*=p(1-w), q*=q(1+w), let normalization drift because it isn't
	 worth tracking step by step */
      
      pi>>=shift;
      qi>>=shift;
      qexp+=shift-7*m;

      pi=((pi*pi)>>16);
      qi=((qi*qi)>>16);
      qexp=qexp*2+m;
      
      pi*=(1<<14)-wi;
      qi*=(1<<14)+wi;
      qi=(qi+pi)>>14;
      
    }
    

    /* we've let the normalization drift because it wasn't important;
       however, for the lookup, things must be normalized again.  We
       need at most one right shift or a number of left shifts */

    if(qi&0xffff0000){ /* checks for 1.xxxxxxxxxxxxxxxx */
      qi>>=1; qexp++; 
    }else
      while(qi && !(qi&0x8000)){ /* checks for 0.0xxxxxxxxxxxxxxx or less*/
	qi<<=1; qexp--; 
      }

#endif

    amp=vorbis_fromdBlook_i(ampi*                     /*  n.4         */
			    vorbis_invsqlook_i(qi,qexp)- 
			                              /*  m.8, m+n<=8 */
			    ampoffseti);              /*  8.12[0]     */
    
#ifdef _LOW_ACCURACY_
    amp>>=9;
#endif
    curve[i]= MULT31_SHIFT15(curve[i],amp);
    while(map[++i]==k) curve[i]= MULT31_SHIFT15(curve[i],amp);
  }
}