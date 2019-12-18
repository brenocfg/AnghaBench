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
struct TYPE_3__ {int* buf; unsigned int buf_size; char* filename; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ AVProbeData ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 scalar_t__ AVPROBE_PADDING_SIZE ; 
 scalar_t__ AV_READ_TIME () ; 
 scalar_t__ FFMAX (unsigned int,int) ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,int) ; 
 int* av_realloc (int*,scalar_t__) ; 
 int failures ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int*,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  print_times () ; 
 int /*<<< orphan*/  probe (TYPE_1__*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,unsigned int) ; 
 int read_int (char*) ; 
 char* single_format ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int main(int argc, char **argv)
{
    unsigned int p, i, type, size, retry;
    AVProbeData pd = { 0 };
    AVLFG state;
    PutBitContext pb;
    int retry_count= 4097;
    int max_size = 65537;
    int j;

    for (j = i = 1; i<argc; i++) {
        if (!strcmp(argv[i], "-f") && i+1<argc && !single_format) {
            single_format = argv[++i];
        } else if (read_int(argv[i])>0 && j == 1) {
            retry_count = read_int(argv[i]);
            j++;
        } else if (read_int(argv[i])>0 && j == 2) {
            max_size = read_int(argv[i]);
            j++;
        } else {
            fprintf(stderr, "probetest [-f <input format>] [<retry_count> [<max_size>]]\n");
            return 1;
        }
    }

    if (max_size > 1000000000U/8) {
        fprintf(stderr, "max_size out of bounds\n");
        return 1;
    }

    if (retry_count > 1000000000U) {
        fprintf(stderr, "retry_count out of bounds\n");
        return 1;
    }

    av_lfg_init(&state, 0xdeadbeef);

    pd.buf = NULL;
    for (size = 1; size < max_size; size *= 2) {
        pd.buf_size = size;
        pd.buf      = av_realloc(pd.buf, size + AVPROBE_PADDING_SIZE);
        pd.filename = "";

        if (!pd.buf) {
            fprintf(stderr, "out of memory\n");
            return 1;
        }

        memset(pd.buf, 0, size + AVPROBE_PADDING_SIZE);

        fprintf(stderr, "testing size=%d\n", size);

        for (retry = 0; retry < retry_count; retry += FFMAX(size, 32)) {
            for (type = 0; type < 4; type++) {
                for (p = 0; p < 4096; p++) {
                    unsigned hist = 0;
                    init_put_bits(&pb, pd.buf, size);
                    switch (type) {
                    case 0:
                        for (i = 0; i < size * 8; i++)
                            put_bits(&pb, 1, (av_lfg_get(&state) & 0xFFFFFFFF) > p << 20);
                        break;
                    case 1:
                        for (i = 0; i < size * 8; i++) {
                            unsigned int p2 = hist ? p & 0x3F : (p >> 6);
                            unsigned int v  = (av_lfg_get(&state) & 0xFFFFFFFF) > p2 << 26;
                            put_bits(&pb, 1, v);
                            hist = v;
                        }
                        break;
                    case 2:
                        for (i = 0; i < size * 8; i++) {
                            unsigned int p2 = (p >> (hist * 3)) & 7;
                            unsigned int v  = (av_lfg_get(&state) & 0xFFFFFFFF) > p2 << 29;
                            put_bits(&pb, 1, v);
                            hist = (2 * hist + v) & 3;
                        }
                        break;
                    case 3:
                        for (i = 0; i < size; i++) {
                            int c = 0;
                            while (p & 63) {
                                c = (av_lfg_get(&state) & 0xFFFFFFFF) >> 24;
                                if (c >= 'a' && c <= 'z' && (p & 1))
                                    break;
                                else if (c >= 'A' && c <= 'Z' && (p & 2))
                                    break;
                                else if (c >= '0' && c <= '9' && (p & 4))
                                    break;
                                else if (c == ' ' && (p & 8))
                                    break;
                                else if (c == 0 && (p & 16))
                                    break;
                                else if (c == 1 && (p & 32))
                                    break;
                            }
                            pd.buf[i] = c;
                        }
                    }
                    flush_put_bits(&pb);
                    probe(&pd, type, p, size);
                }
            }
        }
    }
    if(AV_READ_TIME())
        print_times();
    return failures;
}