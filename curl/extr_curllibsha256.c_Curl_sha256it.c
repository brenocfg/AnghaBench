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
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curlx_uztoui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void Curl_sha256it(unsigned char *outbuffer, /* 32 unsigned chars */
                   const unsigned char *input)
{
  SHA256_CTX ctx;
  SHA256_Init(&ctx);
  SHA256_Update(&ctx, input, curlx_uztoui(strlen((char *)input)));
  SHA256_Final(outbuffer, &ctx);
}