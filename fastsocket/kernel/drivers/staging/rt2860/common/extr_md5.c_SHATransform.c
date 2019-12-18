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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT32 ;

/* Variables and functions */
 int CYCLIC_LEFT_SHIFT (int,int) ; 
 int /*<<< orphan*/  SHA1Step (int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SHA1_F1 ; 
 int /*<<< orphan*/  SHA1_F2 ; 
 int /*<<< orphan*/  SHA1_F3 ; 

VOID SHATransform(UINT32 Buf[5], UINT32 Mes[20])
{
    UINT32 Reg[5],Temp;
	unsigned int i;
    UINT32 W[80];

    static UINT32 SHA1Table[4] = { 0x5a827999, 0x6ed9eba1,
                                  0x8f1bbcdc, 0xca62c1d6 };

    Reg[0]=Buf[0];
	Reg[1]=Buf[1];
	Reg[2]=Buf[2];
	Reg[3]=Buf[3];
	Reg[4]=Buf[4];

    //the first octet of a word is stored in the 0th element, bytereverse
	for(i = 0; i < 16; i++)
    {
    	W[i]  = (Mes[i] >> 24) & 0xff;
        W[i] |= (Mes[i] >> 8 ) & 0xff00;
        W[i] |= (Mes[i] << 8 ) & 0xff0000;
        W[i] |= (Mes[i] << 24) & 0xff000000;
    }


    for	(i = 0; i < 64; i++)
	    W[16+i] = CYCLIC_LEFT_SHIFT(W[i] ^ W[2+i] ^ W[8+i] ^ W[13+i], 1);


    // 80 steps in SHA-1 algorithm
    for (i=0; i<80; i++)
    {
        if (i<20)
            SHA1Step(SHA1_F1, Reg[0], Reg[1], Reg[2], Reg[3], Reg[4],
                     W[i], SHA1Table[0]);

        else if (i>=20 && i<40)
            SHA1Step(SHA1_F2, Reg[0], Reg[1], Reg[2], Reg[3], Reg[4],
                     W[i], SHA1Table[1]);

		else if (i>=40 && i<60)
            SHA1Step(SHA1_F3, Reg[0], Reg[1], Reg[2], Reg[3], Reg[4],
                      W[i], SHA1Table[2]);

        else
            SHA1Step(SHA1_F2, Reg[0], Reg[1], Reg[2], Reg[3], Reg[4],
                     W[i], SHA1Table[3]);


       // one-word right shift
		Temp   = Reg[4];
        Reg[4] = Reg[3];
        Reg[3] = Reg[2];
        Reg[2] = Reg[1];
        Reg[1] = Reg[0];
        Reg[0] = Temp;

    } // end of for-loop


    // (temporary)output
    for (i=0; i<5; i++)
        Buf[i] += Reg[i];

}