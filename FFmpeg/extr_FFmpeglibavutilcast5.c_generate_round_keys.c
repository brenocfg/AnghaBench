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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_X ; 
 int /*<<< orphan*/  COMPUTE_Z ; 
 size_t IA (int) ; 
 size_t IB (int) ; 
 size_t IC (int) ; 
 size_t ID (int) ; 
 int* S5 ; 
 int* S6 ; 
 int* S7 ; 
 int* S8 ; 

__attribute__((used)) static void generate_round_keys(int rnds, uint32_t* K, uint32_t* x, uint32_t* z)
{
    COMPUTE_Z;

    K[1] = S5[IA(z[2])] ^ S6[IB(z[2])] ^ S7[ID(z[1])] ^ S8[IC(z[1])] ^ S5[IC(z[0])];
    K[2] = S5[IC(z[2])] ^ S6[ID(z[2])] ^ S7[IB(z[1])] ^ S8[IA(z[1])] ^ S6[IC(z[1])];
    K[3] = S5[IA(z[3])] ^ S6[IB(z[3])] ^ S7[ID(z[0])] ^ S8[IC(z[0])] ^ S7[IB(z[2])];
    K[4] = S5[IC(z[3])] ^ S6[ID(z[3])] ^ S7[IB(z[0])] ^ S8[IA(z[0])] ^ S8[IA(z[3])];

    COMPUTE_X;

    K[5] = S5[ID(x[0])] ^ S6[IC(x[0])] ^ S7[IA(x[3])] ^ S8[IB(x[3])] ^ S5[IA(x[2])];
    K[6] = S5[IB(x[0])] ^ S6[IA(x[0])] ^ S7[IC(x[3])] ^ S8[ID(x[3])] ^ S6[IB(x[3])];
    K[7] = S5[ID(x[1])] ^ S6[IC(x[1])] ^ S7[IA(x[2])] ^ S8[IB(x[2])] ^ S7[ID(x[0])];
    K[8] = S5[IB(x[1])] ^ S6[IA(x[1])] ^ S7[IC(x[2])] ^ S8[ID(x[2])] ^ S8[ID(x[1])];

    COMPUTE_Z;

    K[9] = S5[ID(z[0])] ^ S6[IC(z[0])] ^ S7[IA(z[3])] ^ S8[IB(z[3])] ^ S5[IB(z[2])];
    K[10] = S5[IB(z[0])] ^ S6[IA(z[0])] ^ S7[IC(z[3])] ^ S8[ID(z[3])] ^ S6[IA(z[3])];
    K[11] = S5[ID(z[1])] ^ S6[IC(z[1])] ^ S7[IA(z[2])] ^ S8[IB(z[2])] ^ S7[IC(z[0])];
    K[12] = S5[IB(z[1])] ^ S6[IA(z[1])] ^ S7[IC(z[2])] ^ S8[ID(z[2])] ^ S8[IC(z[1])];

    COMPUTE_X;

    if (rnds == 16) {
        K[13] = S5[IA(x[2])] ^ S6[IB(x[2])] ^ S7[ID(x[1])] ^ S8[IC(x[1])] ^ S5[ID(x[0])];
        K[14] = S5[IC(x[2])] ^ S6[ID(x[2])] ^ S7[IB(x[1])] ^ S8[IA(x[1])] ^ S6[ID(x[1])];
        K[15] = S5[IA(x[3])] ^ S6[IB(x[3])] ^ S7[ID(x[0])] ^ S8[IC(x[0])] ^ S7[IA(x[2])];
        K[16] = S5[IC(x[3])] ^ S6[ID(x[3])] ^ S7[IB(x[0])] ^ S8[IA(x[0])] ^ S8[IB(x[3])];
    }
}