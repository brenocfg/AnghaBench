#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ flag; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {char* bench_pattern; char* test_name; int num_failed; int num_checked; int /*<<< orphan*/  funcs; int /*<<< orphan*/  bench_pattern_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_get_cpu_flags () ; 
 unsigned int av_get_random_seed () ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ bench_init () ; 
 int /*<<< orphan*/  bench_uninit () ; 
 int /*<<< orphan*/  check_cpu_flag (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  checkasm_checked_call ; 
 int /*<<< orphan*/  checkasm_checked_call_vfp ; 
 int /*<<< orphan*/  checkasm_lfg ; 
 TYPE_3__* cpus ; 
 int /*<<< orphan*/  destroy_func_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ have_neon (int /*<<< orphan*/ ) ; 
 scalar_t__ have_vfp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_benchs (int /*<<< orphan*/ ) ; 
 TYPE_2__ state ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* tests ; 

int main(int argc, char *argv[])
{
    unsigned int seed = av_get_random_seed();
    int i, ret = 0;

#if ARCH_ARM && HAVE_ARMV5TE_EXTERNAL
    if (have_vfp(av_get_cpu_flags()) || have_neon(av_get_cpu_flags()))
        checkasm_checked_call = checkasm_checked_call_vfp;
#endif

    if (!tests[0].func || !cpus[0].flag) {
        fprintf(stderr, "checkasm: no tests to perform\n");
        return 0;
    }

    while (argc > 1) {
        if (!strncmp(argv[1], "--bench", 7)) {
            if (bench_init() < 0)
                return 1;
            if (argv[1][7] == '=') {
                state.bench_pattern = argv[1] + 8;
                state.bench_pattern_len = strlen(state.bench_pattern);
            } else
                state.bench_pattern = "";
        } else if (!strncmp(argv[1], "--test=", 7)) {
            state.test_name = argv[1] + 7;
        } else {
            seed = strtoul(argv[1], NULL, 10);
        }

        argc--;
        argv++;
    }

    fprintf(stderr, "checkasm: using random seed %u\n", seed);
    av_lfg_init(&checkasm_lfg, seed);

    check_cpu_flag(NULL, 0);
    for (i = 0; cpus[i].flag; i++)
        check_cpu_flag(cpus[i].name, cpus[i].flag);

    if (state.num_failed) {
        fprintf(stderr, "checkasm: %d of %d tests have failed\n", state.num_failed, state.num_checked);
        ret = 1;
    } else {
        fprintf(stderr, "checkasm: all %d tests passed\n", state.num_checked);
        if (state.bench_pattern) {
            print_benchs(state.funcs);
        }
    }

    destroy_func_tree(state.funcs);
    bench_uninit();
    return ret;
}