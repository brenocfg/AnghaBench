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
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Step (int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  MD5_F1 ; 
 int /*<<< orphan*/  MD5_F2 ; 
 int /*<<< orphan*/  MD5_F3 ; 
 int /*<<< orphan*/  MD5_F4 ; 

VOID MD5Transform(UINT32 Buf[4], UINT32 Mes[16])
{
    UINT32 Reg[4], Temp;
	unsigned int i;

    static UCHAR LShiftVal[16] =
    {
        7, 12, 17, 22,
		5, 9 , 14, 20,
		4, 11, 16, 23,
 		6, 10, 15, 21,
 	};


	// [equal to 4294967296*abs(sin(index))]
    static UINT32 MD5Table[64] =
	{
		0xd76aa478,	0xe8c7b756,	0x242070db,	0xc1bdceee,
		0xf57c0faf,	0x4787c62a,	0xa8304613, 0xfd469501,
		0x698098d8,	0x8b44f7af,	0xffff5bb1,	0x895cd7be,
    	0x6b901122,	0xfd987193,	0xa679438e,	0x49b40821,

    	0xf61e2562,	0xc040b340,	0x265e5a51,	0xe9b6c7aa,
    	0xd62f105d,	0x02441453,	0xd8a1e681,	0xe7d3fbc8,
    	0x21e1cde6,	0xc33707d6,	0xf4d50d87,	0x455a14ed,
    	0xa9e3e905,	0xfcefa3f8,	0x676f02d9,	0x8d2a4c8a,

    	0xfffa3942,	0x8771f681,	0x6d9d6122,	0xfde5380c,
    	0xa4beea44,	0x4bdecfa9,	0xf6bb4b60,	0xbebfbc70,
    	0x289b7ec6,	0xeaa127fa,	0xd4ef3085,	0x04881d05,
    	0xd9d4d039,	0xe6db99e5,	0x1fa27cf8,	0xc4ac5665,

    	0xf4292244,	0x432aff97,	0xab9423a7,	0xfc93a039,
   		0x655b59c3,	0x8f0ccc92,	0xffeff47d,	0x85845dd1,
    	0x6fa87e4f,	0xfe2ce6e0,	0xa3014314,	0x4e0811a1,
    	0xf7537e82,	0xbd3af235,	0x2ad7d2bb,	0xeb86d391
	};


    for (i=0; i<4; i++)
        Reg[i]=Buf[i];


    // 64 steps in MD5 algorithm
    for (i=0; i<16; i++)
    {
        MD5Step(MD5_F1, Reg[0], Reg[1], Reg[2], Reg[3], Mes[i],
                MD5Table[i], LShiftVal[i & 0x3]);

        // one-word right shift
        Temp   = Reg[3];
        Reg[3] = Reg[2];
        Reg[2] = Reg[1];
        Reg[1] = Reg[0];
        Reg[0] = Temp;
    }
    for (i=16; i<32; i++)
    {
        MD5Step(MD5_F2, Reg[0], Reg[1], Reg[2], Reg[3], Mes[(5*(i & 0xf)+1) & 0xf],
                MD5Table[i], LShiftVal[(0x1 << 2)+(i & 0x3)]);

        // one-word right shift
        Temp   = Reg[3];
        Reg[3] = Reg[2];
        Reg[2] = Reg[1];
        Reg[1] = Reg[0];
        Reg[0] = Temp;
    }
    for (i=32; i<48; i++)
    {
        MD5Step(MD5_F3, Reg[0], Reg[1], Reg[2], Reg[3], Mes[(3*(i & 0xf)+5) & 0xf],
                MD5Table[i], LShiftVal[(0x1 << 3)+(i & 0x3)]);

        // one-word right shift
        Temp   = Reg[3];
        Reg[3] = Reg[2];
        Reg[2] = Reg[1];
        Reg[1] = Reg[0];
        Reg[0] = Temp;
    }
    for (i=48; i<64; i++)
    {
        MD5Step(MD5_F4, Reg[0], Reg[1], Reg[2], Reg[3], Mes[(7*(i & 0xf)) & 0xf],
                MD5Table[i], LShiftVal[(0x3 << 2)+(i & 0x3)]);

        // one-word right shift
        Temp   = Reg[3];
        Reg[3] = Reg[2];
        Reg[2] = Reg[1];
        Reg[1] = Reg[0];
        Reg[0] = Temp;
    }


    // (temporary)output
    for (i=0; i<4; i++)
        Buf[i] += Reg[i];

}