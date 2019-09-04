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

/* Variables and functions */
 int* FORMATS ; 
 int* SAMPLE_RATES ; 
 int /*<<< orphan*/  check_device_sanity_with_params (char const*,int,int,int) ; 
 int countof (int*) ; 

__attribute__((used)) static void check_device_sanity(const char *name) {
    for(int si=0 ; si<countof(SAMPLE_RATES) ; ++si) {
        for(int fi=0 ; fi<countof(FORMATS) ; ++fi) {
            // 8 seconds of data
            check_device_sanity_with_params(
                name, SAMPLE_RATES[si], FORMATS[fi], 8*SAMPLE_RATES[si]
            );
        }
    }
}