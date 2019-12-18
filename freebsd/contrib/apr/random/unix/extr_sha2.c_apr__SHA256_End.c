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
typedef  int sha2_byte ;
typedef  int SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MEMSET_BZERO (int*,int) ; 
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  apr__SHA256_Final (int*,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 void** sha2_hex_digits ; 

char *apr__SHA256_End(SHA256_CTX* context, char buffer[]) {
        sha2_byte       digest[SHA256_DIGEST_LENGTH], *d = digest;
        int             i;

        /* Sanity check: */
        assert(context != (SHA256_CTX*)0);

        if (buffer != (char*)0) {
                apr__SHA256_Final(digest, context);

                for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
                        *buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
                        *buffer++ = sha2_hex_digits[*d & 0x0f];
                        d++;
                }
                *buffer = (char)0;
        } else {
                MEMSET_BZERO(context, sizeof(*context));
        }
        MEMSET_BZERO(digest, SHA256_DIGEST_LENGTH);
        return buffer;
}