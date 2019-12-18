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
typedef  int u32 ;
typedef  size_t BYTE ;

/* Variables and functions */
 size_t* Q0 ; 
 size_t* Q1 ; 
 size_t b0 (int) ; 
 size_t b1 (int) ; 
 size_t b2 (int) ; 
 size_t b3 (int) ; 
 int* mult5B ; 
 int* multEF ; 

void fullKey(u32 L[4], int k, u32 QF[4][256])
{
    BYTE y0, y1, y2, y3;

    int i;
    
    /* for all input values to the Q permutations */
    for (i=0; i<256; i++)
    {
	/* run the Q permutations */
	y0 = i; y1=i; y2=i; y3=i;
	switch(k)
    	{
    	    case 4:
    		y0 = Q1[y0] ^ b0(L[3]);
    		y1 = Q0[y1] ^ b1(L[3]);
    		y2 = Q0[y2] ^ b2(L[3]);
    		y3 = Q1[y3] ^ b3(L[3]);
    	    case 3:
    		y0 = Q1[y0] ^ b0(L[2]);
    		y1 = Q1[y1] ^ b1(L[2]);
    		y2 = Q0[y2] ^ b2(L[2]);
    		y3 = Q0[y3] ^ b3(L[2]);
    	    case 2:
    		y0 = Q1[  Q0 [ Q0[y0] ^ b0(L[1]) ] ^ b0(L[0]) ];
    		y1 = Q0[  Q0 [ Q1[y1] ^ b1(L[1]) ] ^ b1(L[0]) ];
    		y2 = Q1[  Q1 [ Q0[y2] ^ b2(L[1]) ] ^ b2(L[0]) ];
    		y3 = Q0[  Q1 [ Q1[y3] ^ b3(L[1]) ] ^ b3(L[0]) ];
    	}
	
	/* now do the partial MDS matrix multiplies */
	QF[0][i] = ((multEF[y0] << 24) 
		    | (multEF[y0] << 16) 
		    | (mult5B[y0] << 8)
		    | y0);
	QF[1][i] = ((y1 << 24) 
		    | (mult5B[y1] << 16) 
		    | (multEF[y1] << 8)
		    | multEF[y1]);
	QF[2][i] = ((multEF[y2] << 24) 
		    | (y2 << 16) 
		    | (multEF[y2] << 8)
		    | mult5B[y2]);
	QF[3][i] = ((mult5B[y3] << 24) 
		    | (multEF[y3] << 16)
		    | (y3 << 8) 
		    | mult5B[y3]);
    }
}