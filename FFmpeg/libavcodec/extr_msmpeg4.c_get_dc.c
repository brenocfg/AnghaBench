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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int FASTDIV (int,int) ; 

__attribute__((used)) static int get_dc(uint8_t *src, int stride, int scale, int block_size)
{
    int y;
    int sum=0;
    for(y=0; y<block_size; y++){
        int x;
        for(x=0; x<block_size; x++){
            sum+=src[x + y*stride];
        }
    }
    return FASTDIV((sum + (scale>>1)), scale);
}