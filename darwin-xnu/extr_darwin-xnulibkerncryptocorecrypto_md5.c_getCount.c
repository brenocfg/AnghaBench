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
typedef  int uint64_t ;
struct TYPE_3__ {int* count; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */

__attribute__((used)) static uint64_t getCount(MD5_CTX *ctx)
{
	return ( (((uint64_t)ctx->count[0])<<32) | (ctx->count[1]) );
}