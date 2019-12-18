#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flag; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int IPERF_FLAG_CLIENT ; 
 int IPERF_FLAG_UDP ; 
 TYPE_2__ s_iperf_ctrl ; 

__attribute__((used)) inline static bool iperf_is_udp_client(void)
{
    return ((s_iperf_ctrl.cfg.flag & IPERF_FLAG_CLIENT) && (s_iperf_ctrl.cfg.flag & IPERF_FLAG_UDP));
}