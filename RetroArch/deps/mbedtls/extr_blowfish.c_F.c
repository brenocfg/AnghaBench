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
typedef  int uint32_t ;
struct TYPE_3__ {int** S; } ;
typedef  TYPE_1__ mbedtls_blowfish_context ;

/* Variables and functions */

__attribute__((used)) static uint32_t F( mbedtls_blowfish_context *ctx, uint32_t x )
{
   unsigned short a, b, c, d;
   uint32_t  y;

   d = (unsigned short)(x & 0xFF);
   x >>= 8;
   c = (unsigned short)(x & 0xFF);
   x >>= 8;
   b = (unsigned short)(x & 0xFF);
   x >>= 8;
   a = (unsigned short)(x & 0xFF);
   y = ctx->S[0][a] + ctx->S[1][b];
   y = y ^ ctx->S[2][c];
   y = y + ctx->S[3][d];

   return( y );
}