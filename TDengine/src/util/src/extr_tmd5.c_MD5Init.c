#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_4__ {void** buf; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void MD5Init(MD5_CTX *mdContext) {
  memset(mdContext, 0, sizeof(MD5_CTX));

  /* Load magic initialization constants. */
  mdContext->buf[0] = (uint32_t)0x67452301;
  mdContext->buf[1] = (uint32_t)0xefcdab89;
  mdContext->buf[2] = (uint32_t)0x98badcfe;
  mdContext->buf[3] = (uint32_t)0x10325476;
}