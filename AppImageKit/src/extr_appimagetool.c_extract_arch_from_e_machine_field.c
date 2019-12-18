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
typedef  int int16_t ;
typedef  char gchar ;

/* Variables and functions */
 size_t fARCH_aarch64 ; 
 size_t fARCH_arm ; 
 size_t fARCH_i386 ; 
 size_t fARCH_x86_64 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

void extract_arch_from_e_machine_field(int16_t e_machine, const gchar* sourcename, bool* archs) {
    if (e_machine == 3) {
        archs[fARCH_i386] = 1;
        if(verbose)
            fprintf(stderr, "%s used for determining architecture i386\n", sourcename);
    }

    if (e_machine == 62) {
        archs[fARCH_x86_64] = 1;
        if(verbose)
            fprintf(stderr, "%s used for determining architecture x86_64\n", sourcename);
    }

    if (e_machine == 40) {
        archs[fARCH_arm] = 1;
        if(verbose)
            fprintf(stderr, "%s used for determining architecture armhf\n", sourcename);
    }

    if (e_machine == 183) {
        archs[fARCH_aarch64] = 1;
        if(verbose)
            fprintf(stderr, "%s used for determining architecture aarch64\n", sourcename);
    }
}