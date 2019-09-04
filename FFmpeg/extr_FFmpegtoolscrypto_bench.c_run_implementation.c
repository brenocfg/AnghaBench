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
typedef  scalar_t__ uint64_t ;
struct hash_impl {char* lib; char* name; int /*<<< orphan*/  (* run ) (int*,int const*,unsigned int) ;scalar_t__ output; } ;

/* Variables and functions */
 scalar_t__ AV_READ_TIME () ; 
 int MAX_OUTPUT_SIZE ; 
 int /*<<< orphan*/  av_stristr (scalar_t__,char*) ; 
 int crc32 (int*,unsigned int) ; 
 scalar_t__ enabled_algos ; 
 scalar_t__ enabled_libs ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int memcmp (int*,int*,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,unsigned int,unsigned int,double,double) ; 
 int specified_runs ; 
 double sqrt (double) ; 
 int /*<<< orphan*/  sscanf (scalar_t__,char*,unsigned int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int*,int const*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int*,int const*,unsigned int) ; 

__attribute__((used)) static void run_implementation(const uint8_t *input, uint8_t *output,
                               struct hash_impl *impl, unsigned size)
{
    uint64_t t0, t1;
    unsigned nruns = specified_runs ? specified_runs : (1 << 30) / size;
    unsigned outlen = 0, outcrc = 0;
    unsigned i, j, val;
    double mtime, ttime = 0, ttime2 = 0, stime;
    uint8_t outref[MAX_OUTPUT_SIZE];

    if (enabled_libs  && !av_stristr(enabled_libs,  impl->lib) ||
        enabled_algos && !av_stristr(enabled_algos, impl->name))
        return;
    if (!sscanf(impl->output, "crc:%x", &outcrc)) {
        outlen = strlen(impl->output) / 2;
        for (i = 0; i < outlen; i++) {
            sscanf(impl->output + i * 2, "%02x", &val);
            outref[i] = val;
        }
    }
    for (i = 0; i < 8; i++) /* heat caches */
        impl->run(output, input, size);
    for (i = 0; i < nruns; i++) {
        memset(output, 0, size); /* avoid leftovers from previous runs */
        t0 = AV_READ_TIME();
        impl->run(output, input, size);
        t1 = AV_READ_TIME();
        if (outlen ? memcmp(output, outref, outlen) :
                     crc32(output, size) != outcrc) {
            fprintf(stderr, "Expected: ");
            if (outlen)
                for (j = 0; j < outlen; j++)
                    fprintf(stderr, "%02x", output[j]);
            else
                fprintf(stderr, "%08x", crc32(output, size));
            fprintf(stderr, "\n");
            fatal_error("output mismatch");
        }
        mtime = (double)(t1 - t0) / size;
        ttime  += mtime;
        ttime2 += mtime * mtime;
    }

    ttime  /= nruns;
    ttime2 /= nruns;
    stime = sqrt(ttime2 - ttime * ttime);
    printf("%-10s %-12s size: %7d  runs: %6d  time: %8.3f +- %.3f\n",
           impl->lib, impl->name, size, nruns, ttime, stime);
    fflush(stdout);
}