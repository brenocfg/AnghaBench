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
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curlx_uztoui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void Curl_md5it(unsigned char *outbuffer, /* 16 bytes */
                const unsigned char *input)
{
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, input, curlx_uztoui(strlen((char *)input)));
  MD5_Final(outbuffer, &ctx);
}