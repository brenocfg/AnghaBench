#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nop_time; } ;

/* Variables and functions */
 int bench_init_ffmpeg () ; 
 int bench_init_linux () ; 
 int measure_nop_time () ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 TYPE_1__ state ; 

__attribute__((used)) static int bench_init(void)
{
#if CONFIG_LINUX_PERF
    int ret = bench_init_linux();
#else
    int ret = bench_init_ffmpeg();
#endif
    if (ret < 0)
        return ret;

    state.nop_time = measure_nop_time();
    printf("nop: %d.%d\n", state.nop_time/10, state.nop_time%10);
    return 0;
}