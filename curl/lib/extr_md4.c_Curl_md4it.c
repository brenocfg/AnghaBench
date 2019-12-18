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
typedef  int /*<<< orphan*/  MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD4_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4_Update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curlx_uztoui (size_t) ; 

void Curl_md4it(unsigned char *output, const unsigned char *input, size_t len)
{
  MD4_CTX ctx;
  MD4_Init(&ctx);
  MD4_Update(&ctx, input, curlx_uztoui(len));
  MD4_Final(output, &ctx);
}