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
typedef  int uint8_t ;
struct AVHashContext {int dummy; } ;

/* Variables and functions */
 int AV_HASH_MAX_SIZE ; 
 unsigned int FFMIN (unsigned int,int) ; 
 int /*<<< orphan*/  av_hash_final (struct AVHashContext*,int*) ; 
 unsigned int av_hash_get_size (struct AVHashContext*) ; 
 int /*<<< orphan*/  snprintf (int*,int,char*,int) ; 

void av_hash_final_hex(struct AVHashContext *ctx, uint8_t *dst, int size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    for (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}