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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int UINT32_MAX ; 
 int abs (int) ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  checked_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 unsigned long long ran () ; 
 void* state ; 

int main(int argc, char **argv)
{
    FILE *f;
    int count, maxburst, length;

    if (argc < 5) {
        printf("USAGE: trasher <filename> <count> <maxburst> <seed>\n");
        return 1;
    }

    f = fopen(argv[1], "rb+");
    if (!f) {
        perror(argv[1]);
        return 2;
    }
    count    = atoi(argv[2]);
    maxburst = atoi(argv[3]);
    state    = atoi(argv[4]);

    checked_seek(f, 0, SEEK_END);
    length = ftell(f);
    checked_seek(f, 0, SEEK_SET);

    while (count--) {
        int burst = 1 + ran() * (uint64_t) (abs(maxburst) - 1) / UINT32_MAX;
        int pos   = ran() * (uint64_t) length / UINT32_MAX;
        checked_seek(f, pos, SEEK_SET);

        if (maxburst < 0)
            burst = -maxburst;

        if (pos + burst > length)
            continue;

        while (burst--) {
            int val = ran() * 256ULL / UINT32_MAX;

            if (maxburst < 0)
                val = 0;

            fwrite(&val, 1, 1, f);
        }
    }

    return 0;
}