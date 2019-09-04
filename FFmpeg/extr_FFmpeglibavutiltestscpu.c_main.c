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
typedef  int /*<<< orphan*/  threads ;
struct TYPE_2__ {char* name; scalar_t__ flag; } ;

/* Variables and functions */
 int av_cpu_count () ; 
 int /*<<< orphan*/  av_force_cpu_flags (unsigned int) ; 
 void* av_get_cpu_flags () ; 
 scalar_t__ av_parse_cpu_caps (unsigned int*,char*) ; 
 int av_strlcpy (char*,char*,int) ; 
 TYPE_1__* cpu_flag_tab ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  print_cpu_flags (int,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    int cpu_flags_raw = av_get_cpu_flags();
    int cpu_flags_eff;
    int cpu_count = av_cpu_count();
    char threads[5] = "auto";
    int i;

    for(i = 0; cpu_flag_tab[i].flag; i++) {
        unsigned tmp = 0;
        if (av_parse_cpu_caps(&tmp, cpu_flag_tab[i].name) < 0) {
            fprintf(stderr, "Table missing %s\n", cpu_flag_tab[i].name);
            return 4;
        }
    }

    if (cpu_flags_raw < 0)
        return 1;

    for (;;) {
        int c = getopt(argc, argv, "c:t:");
        if (c == -1)
            break;
        switch (c) {
        case 'c':
        {
            unsigned flags = av_get_cpu_flags();
            if (av_parse_cpu_caps(&flags, optarg) < 0)
                return 2;

            av_force_cpu_flags(flags);
            break;
        }
        case 't':
        {
            int len = av_strlcpy(threads, optarg, sizeof(threads));
            if (len >= sizeof(threads)) {
                fprintf(stderr, "Invalid thread count '%s'\n", optarg);
                return 2;
            }
        }
        }
    }

    cpu_flags_eff = av_get_cpu_flags();

    if (cpu_flags_eff < 0)
        return 3;

    print_cpu_flags(cpu_flags_raw, "raw");
    print_cpu_flags(cpu_flags_eff, "effective");
    printf("threads = %s (cpu_count = %d)\n", threads, cpu_count);

    return 0;
}