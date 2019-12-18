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
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  bcopy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  bzero (unsigned char*,int) ; 

void
hmac_md5(unsigned char *text, int text_len, unsigned char *key, int key_len,
    unsigned char* digest)
{
        MD5_CTX context;
        unsigned char k_ipad[65];    /* inner padding -
                                      * key XORd with ipad
                                      */
        unsigned char k_opad[65];    /* outer padding -
                                      * key XORd with opad
                                      */
        unsigned char tk[16];
        int i;
        /* if key is longer than 64 bytes reset it to key=MD5(key) */
        if (key_len > 64) {

                MD5_CTX      tctx;

                MD5_Init(&tctx);
                MD5_Update(&tctx, key, key_len);
                MD5_Final(tk, &tctx);

                key = tk;
                key_len = 16;
        }

        /*
         * the HMAC_MD5 transform looks like:
         *
         * MD5(K XOR opad, MD5(K XOR ipad, text))
         *
         * where K is an n byte key
         * ipad is the byte 0x36 repeated 64 times
	 *
         * opad is the byte 0x5c repeated 64 times
         * and text is the data being protected
         */

        /* start out by storing key in pads */
        bzero( k_ipad, sizeof k_ipad);
        bzero( k_opad, sizeof k_opad);
        bcopy( key, k_ipad, key_len);
        bcopy( key, k_opad, key_len);

        /* XOR key with ipad and opad values */
        for (i=0; i<64; i++) {
                k_ipad[i] ^= 0x36;
                k_opad[i] ^= 0x5c;
        }
        /*
         * perform inner MD5
         */
        MD5_Init(&context);                   /* init context for 1st
                                              * pass */
        MD5_Update(&context, k_ipad, 64);     /* start with inner pad */
        MD5_Update(&context, text, text_len); /* then text of datagram */
        MD5_Final(digest, &context);          /* finish up 1st pass */
        /*
         * perform outer MD5
         */
        MD5_Init(&context);                   /* init context for 2nd
                                              * pass */
        MD5_Update(&context, k_opad, 64);     /* start with outer pad */
        MD5_Update(&context, digest, 16);     /* then results of 1st
                                              * hash */
        MD5_Final(digest, &context);          /* finish up 2nd pass */
}