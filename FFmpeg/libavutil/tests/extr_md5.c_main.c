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

/* Variables and functions */
 int /*<<< orphan*/  av_md5_sum (int*,int volatile*,int) ; 
 int /*<<< orphan*/  print_md5 (int*) ; 

int main(void)
{
    uint8_t md5val[16];
    int i;
    volatile uint8_t in[1000]; // volatile to workaround http://llvm.org/bugs/show_bug.cgi?id=20849
    // FIXME remove volatile once it has been fixed and all fate clients are updated

    for (i = 0; i < 1000; i++)
        in[i] = i * i;
    av_md5_sum(md5val, in, 1000);
    print_md5(md5val);
    av_md5_sum(md5val, in, 63);
    print_md5(md5val);
    av_md5_sum(md5val, in, 64);
    print_md5(md5val);
    av_md5_sum(md5val, in, 65);
    print_md5(md5val);
    for (i = 0; i < 1000; i++)
        in[i] = i % 127;
    av_md5_sum(md5val, in, 999);
    print_md5(md5val);

    return 0;
}