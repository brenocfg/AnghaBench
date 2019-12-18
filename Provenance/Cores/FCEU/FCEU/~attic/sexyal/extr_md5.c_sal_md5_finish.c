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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct sal_md5_context {int* total; int* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUT_UINT32 (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * md5_padding ; 
 int /*<<< orphan*/  sal_md5_update (struct sal_md5_context*,int /*<<< orphan*/ *,int) ; 

void sal_md5_finish( struct sal_md5_context *ctx, uint8_t digest[16] )
{
    uint32_t last, padn;
    uint8_t msglen[8];

    PUT_UINT32( ctx->total[0], msglen, 0 );
    PUT_UINT32( ctx->total[1], msglen, 4 );

    last = ( ctx->total[0] >> 3 ) & 0x3F;
    padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last );

    sal_md5_update( ctx, md5_padding, padn );
    sal_md5_update( ctx, msglen, 8 );

    PUT_UINT32( ctx->state[0], digest,  0 );
    PUT_UINT32( ctx->state[1], digest,  4 );
    PUT_UINT32( ctx->state[2], digest,  8 );
    PUT_UINT32( ctx->state[3], digest, 12 );
}