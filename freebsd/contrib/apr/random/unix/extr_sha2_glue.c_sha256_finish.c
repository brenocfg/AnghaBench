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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ apr_crypto_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr__SHA256_Final (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sha256_finish(apr_crypto_hash_t *h,unsigned char *result)
{
    apr__SHA256_Final(result,h->data);
}