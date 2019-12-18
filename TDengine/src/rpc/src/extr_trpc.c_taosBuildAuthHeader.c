#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (TYPE_1__*) ; 
 int /*<<< orphan*/  MD5Init (TYPE_1__*) ; 
 int /*<<< orphan*/  MD5Update (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int TSDB_KEY_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int taosBuildAuthHeader(uint8_t *pMsg, int msgLen, uint8_t *pAuth, uint8_t *pKey) {
  MD5_CTX context;

  MD5Init(&context);
  MD5Update(&context, pKey, TSDB_KEY_LEN);
  MD5Update(&context, (uint8_t *)pMsg, msgLen);
  MD5Update(&context, pKey, TSDB_KEY_LEN);
  MD5Final(&context);

  memcpy(pAuth, context.digest, sizeof(context.digest));

  return 0;
}