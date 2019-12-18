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
struct TYPE_3__ {int freq_mhz; int source_freq_mhz; int div; } ;
typedef  TYPE_1__ rtc_cpu_freq_config_t ;

/* Variables and functions */
 int MHZ ; 

__attribute__((used)) static uint32_t calculateApb(rtc_cpu_freq_config_t * conf){
    if(conf->freq_mhz >= 80){
        return 80 * MHZ;
    }
    return (conf->source_freq_mhz * MHZ) / conf->div;
}