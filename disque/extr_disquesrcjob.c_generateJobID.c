#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  counter ;
struct TYPE_6__ {TYPE_2__* cluster; scalar_t__ jobid_seed; } ;
struct TYPE_5__ {TYPE_1__* myself; } ;
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int CONFIG_RUN_ID_SIZE ; 
 int /*<<< orphan*/  SHA1Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 TYPE_3__ server ; 

void generateJobID(char *id, int ttl, int retry) {
    char *b64cset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz"
                    "0123456789+/";
    char *hexcset = "0123456789abcdef";
    SHA1_CTX ctx;
    unsigned char ttlbytes[2], hash[20];
    int j;
    static uint64_t counter;

    /* Get the pseudo random bytes using SHA1 in counter mode. */
    counter++;
    SHA1Init(&ctx);
    SHA1Update(&ctx,(unsigned char*)server.jobid_seed,CONFIG_RUN_ID_SIZE);
    SHA1Update(&ctx,(unsigned char*)&counter,sizeof(counter));
    SHA1Final(hash,&ctx);

    ttl /= 60; /* Store TTL in minutes. */
    if (ttl > 65535) ttl = 65535;
    if (ttl < 0) ttl = 1;

    /* Force the TTL to be odd if retry > 0, even if retry == 0. */
    ttl = (retry > 0) ? (ttl|1) : (ttl & ~1);

    ttlbytes[0] = (ttl&0xff00)>>8;
    ttlbytes[1] = ttl&0xff;

    *id++ = 'D';
    *id++ = '-';

    /* 8 bytes from Node ID + separator */
    for (j = 0; j < 8; j++) *id++ = server.cluster->myself->name[j];
    *id++ = '-';

    /* Pseudorandom Message ID + separator. We encode 4 base64 chars
     * per loop (3 digest bytes), and each char encodes 6 bits, so we have
     * to loop 6 times to encode all the 144 bits into 24 destination chars. */
    unsigned char *h = hash;
    for (j = 0; j < 6; j++) {
        id[0] = b64cset[h[0]>>2];
        id[1] = b64cset[(h[0]<<4|h[1]>>4)&63];
        id[2] = b64cset[(h[1]<<2|h[2]>>6)&63];
        id[3] = b64cset[h[3]&63];
        id += 4;
        h += 3;
    }
    *id++ = '-';

    /* 4 TTL bytes in hex. */
    id[0] = hexcset[(ttlbytes[0]&0xf0)>>4];
    id[1] = hexcset[ttlbytes[0]&0xf];
    id[2] = hexcset[(ttlbytes[1]&0xf0)>>4];
    id[3] = hexcset[ttlbytes[1]&0xf];
    id += 4;
}