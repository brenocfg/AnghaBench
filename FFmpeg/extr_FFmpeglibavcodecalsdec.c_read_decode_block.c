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
typedef  int /*<<< orphan*/  ALSDecContext ;
typedef  int /*<<< orphan*/  ALSBlockData ;

/* Variables and functions */
 int decode_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_decode_block(ALSDecContext *ctx, ALSBlockData *bd)
{
    int ret;

    if ((ret = read_block(ctx, bd)) < 0)
        return ret;

    return decode_block(ctx, bd);
}