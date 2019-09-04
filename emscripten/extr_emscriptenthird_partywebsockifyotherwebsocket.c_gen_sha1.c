#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  key1; } ;
typedef  TYPE_1__ headers_t ;
typedef  int /*<<< orphan*/  SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  HYBI10_ACCEPTHDRLEN ; 
 int /*<<< orphan*/  HYBI_GUID ; 
 int /*<<< orphan*/  SHA1_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int b64_ntop (unsigned char*,int,char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen_sha1(headers_t *headers, char *target) {
    SHA_CTX c;
    unsigned char hash[SHA_DIGEST_LENGTH];
    int r;

    SHA1_Init(&c);
    SHA1_Update(&c, headers->key1, strlen(headers->key1));
    SHA1_Update(&c, HYBI_GUID, 36);
    SHA1_Final(hash, &c);

    r = b64_ntop(hash, sizeof hash, target, HYBI10_ACCEPTHDRLEN);
    //assert(r == HYBI10_ACCEPTHDRLEN - 1);
}