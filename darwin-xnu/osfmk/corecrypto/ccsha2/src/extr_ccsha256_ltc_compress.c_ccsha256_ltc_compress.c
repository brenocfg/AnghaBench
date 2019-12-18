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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ccdigest_state_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CCSHA256_BLOCK_SIZE ; 
 scalar_t__ Gamma0 (scalar_t__) ; 
 scalar_t__ Gamma1 (scalar_t__) ; 
 int /*<<< orphan*/  RND (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__* ccdigest_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_W (int) ; 

void ccsha256_ltc_compress(ccdigest_state_t state, size_t nblocks, const void *in)
{
    uint32_t W[64], t0, t1;
    uint32_t S0,S1,S2,S3,S4,S5,S6,S7;
    int i;
    uint32_t *s = ccdigest_u32(state);
#if CC_HANDLE_UNALIGNED_DATA
    const unsigned char *buf = in;
#else
    const uint32_t *buf = in;
#endif

    while(nblocks--) {

        // schedule W 0..15
        set_W(0); set_W(1); set_W(2); set_W(3); set_W(4); set_W(5); set_W(6); set_W(7);
        set_W(8); set_W(9); set_W(10);set_W(11);set_W(12);set_W(13);set_W(14);set_W(15);

        // schedule W 16..63
        for (i = 16; i < 64; i++) {
            W[i] = Gamma1(W[i - 2]) + W[i - 7] + Gamma0(W[i - 15]) + W[i - 16];
        }

        // copy state into S
        S0= s[0];
        S1= s[1];
        S2= s[2];
        S3= s[3];
        S4= s[4];
        S5= s[5];
        S6= s[6];
        S7= s[7];

        // Compress
        for (i = 0; i < 64; i += 8) {
            RND(S0,S1,S2,S3,S4,S5,S6,S7,i+0);
            RND(S7,S0,S1,S2,S3,S4,S5,S6,i+1);
            RND(S6,S7,S0,S1,S2,S3,S4,S5,i+2);
            RND(S5,S6,S7,S0,S1,S2,S3,S4,i+3);
            RND(S4,S5,S6,S7,S0,S1,S2,S3,i+4);
            RND(S3,S4,S5,S6,S7,S0,S1,S2,i+5);
            RND(S2,S3,S4,S5,S6,S7,S0,S1,i+6);
            RND(S1,S2,S3,S4,S5,S6,S7,S0,i+7);
        }

        // feedback
        s[0] += S0;
        s[1] += S1;
        s[2] += S2;
        s[3] += S3;
        s[4] += S4;
        s[5] += S5;
        s[6] += S6;
        s[7] += S7;

        buf+=CCSHA256_BLOCK_SIZE/sizeof(buf[0]);
    }
}