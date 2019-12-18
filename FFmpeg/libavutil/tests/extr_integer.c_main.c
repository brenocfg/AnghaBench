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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVInteger ;

/* Variables and functions */
 int /*<<< orphan*/  av_add_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_div_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_i2int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_int2i (int) ; 
 scalar_t__ av_log2 (int) ; 
 scalar_t__ av_log2_i (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_mul_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_shr_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_sub_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void){
    int64_t a,b;

    for(a=7; a<256*256*256; a+=13215){
        for(b=3; b<256*256*256; b+=27118){
            AVInteger ai= av_int2i(a);
            AVInteger bi= av_int2i(b);

            av_assert0(av_i2int(ai) == a);
            av_assert0(av_i2int(bi) == b);
            av_assert0(av_i2int(av_add_i(ai,bi)) == a+b);
            av_assert0(av_i2int(av_sub_i(ai,bi)) == a-b);
            av_assert0(av_i2int(av_mul_i(ai,bi)) == a*b);
            av_assert0(av_i2int(av_shr_i(ai, 9)) == a>>9);
            av_assert0(av_i2int(av_shr_i(ai,-9)) == a<<9);
            av_assert0(av_i2int(av_shr_i(ai, 17)) == a>>17);
            av_assert0(av_i2int(av_shr_i(ai,-17)) == a<<17);
            av_assert0(av_log2_i(ai) == av_log2(a));
            av_assert0(av_i2int(av_div_i(ai,bi)) == a/b);
        }
    }
    return 0;
}