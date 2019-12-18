#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  hexbuf ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_4__ {scalar_t__ cycles; int PC; int SR; int* D; int* A; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEXIT (char*,int,int) ; 
 int READU16 (TYPE_1__*,int) ; 
 int SR_C ; 
 int SR_N ; 
 int SR_V ; 
 int SR_X ; 
 int SR_Z ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  _IOFBF ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * logfile ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 char* q68_disassemble (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 
 TYPE_1__* state ; 
 int strlen (char const*) ; 
 scalar_t__ total_cycles ; 
 scalar_t__ const trace_start ; 
 scalar_t__ const trace_stop ; 

void q68_trace(void)
{
    const uint64_t cycles = total_cycles + state->cycles;

    if (cycles < trace_start) {

        /* Before first instruction: do nothing */

    } else if (cycles >= trace_stop) {

        /* After last instruction: close log file if it's open */
        if (logfile) {
#ifdef __linux__
            pclose(logfile);
#else
            fclose(logfile);
#endif
            logfile = NULL;
        }

    } else {

        if (!logfile) {
#ifdef __linux__
            logfile = popen("gzip -3 >q68.log.gz", "w");
#else
            logfile = fopen("q68.log", "w");
#endif
            if (UNLIKELY(!logfile)) {
                perror("Failed to open trace logfile");
                return;
            }
            setvbuf(logfile, NULL, _IOFBF, 65536);
        }

        int nwords = 1, i;
        const char *disassembled = q68_disassemble(state, state->PC, &nwords);

#ifdef PSP  // because the cleaner fprintf() version is just too slow
        int dislen = strlen(disassembled);
        static char buf1[] =
            "......: .... .... ....  ..........................  SR=.... .....  [..........]\n";
        static char buf2[] =
            "    D: ........ ........ ........ ........ ........ ........ ........ ........\n"
            "    A: ........ ........ ........ ........ ........ ........ ........ ........\n";

        if (nwords > 3) {  // We can only fit 3 words on the line
            nwords = 3;
        }
        HEXIT(&buf1[0], state->PC, 6);
        for (i = 0; i < nwords; i++) {
            HEXIT(&buf1[8+5*i], READU16(state, state->PC+2*i), 4);
        }
        if (i < 3) {
            memset(&buf1[8+5*i], ' ', 4+5*(2-i));
        }
        if (dislen > 26) {  // Pathologically long text needs special handling
            fprintf(logfile, "%.22s  %-26s  SR=%04X %c%c%c%c%c  [%10lld]\n",
                    buf1, disassembled, (int)state->SR,
                    state->SR & SR_X ? 'X' : '.', state->SR & SR_N ? 'N' : '.',
                    state->SR & SR_Z ? 'Z' : '.', state->SR & SR_V ? 'V' : '.',
                    state->SR & SR_C ? 'C' : '.', (unsigned long long)cycles);
        } else {
            memcpy(&buf1[24], disassembled, dislen);
            if (dislen < 26) {
                memset(&buf1[24+dislen], ' ', 26-dislen);
            }
            HEXIT(&buf1[55], state->SR, 4);
            buf1[60] = state->SR & SR_X ? 'X' : '.';
            buf1[61] = state->SR & SR_N ? 'N' : '.';
            buf1[62] = state->SR & SR_Z ? 'Z' : '.';
            buf1[63] = state->SR & SR_V ? 'V' : '.';
            buf1[64] = state->SR & SR_C ? 'C' : '.';
            snprintf(&buf1[68], sizeof(buf1)-68, "%10lld]\n",
                     (unsigned long long)cycles);
            fwrite(buf1, 1, strlen(buf1), logfile);
        }
        for (i = 0; i < 8; i++) {
            HEXIT(&buf2[ 7+9*i], state->D[i], 8);
            HEXIT(&buf2[86+9*i], state->A[i], 8);
        }
        fwrite(buf2, 1, sizeof(buf2)-1, logfile);
#else  // !PSP
        char hexbuf[100];
        int hexlen = 0;

        if (nwords > 3) {  // We can only fit 3 words on the line
            nwords = 3;
        }
        for (i = 0; i < nwords && hexlen < sizeof(hexbuf)-5; i++) {
            hexlen += snprintf(hexbuf+hexlen, sizeof(hexbuf)-hexlen,
                               "%s%04X", hexlen==0 ? "" : " ",
                               (int)READU16(state, state->PC+2*i));
        }

        fprintf(logfile, "%06X: %-14s  %-26s  SR=%04X %c%c%c%c%c  [%10llu]\n"
                         "    D: %08X %08X %08X %08X %08X %08X %08X %08X\n"
                         "    A: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                (int)state->PC, hexbuf, disassembled, (int)state->SR,
                state->SR & SR_X ? 'X' : '.', state->SR & SR_N ? 'N' : '.',
                state->SR & SR_Z ? 'Z' : '.', state->SR & SR_V ? 'V' : '.',
                state->SR & SR_C ? 'C' : '.', (unsigned long long)cycles,
                (int)state->D[0], (int)state->D[1], (int)state->D[2],
                (int)state->D[3], (int)state->D[4], (int)state->D[5],
                (int)state->D[6], (int)state->D[7],
                (int)state->A[0], (int)state->A[1], (int)state->A[2],
                (int)state->A[3], (int)state->A[4], (int)state->A[5],
                (int)state->A[6], (int)state->A[7]
            );
#endif  // PSP

    }  // current_cycles >= trace_start && current_cycles < trace_stop
}