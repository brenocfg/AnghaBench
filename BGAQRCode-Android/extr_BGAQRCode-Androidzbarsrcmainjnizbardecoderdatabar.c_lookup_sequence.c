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
struct TYPE_3__ {int data; } ;
typedef  TYPE_1__ databar_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 unsigned char* exp_sequences ; 

__attribute__((used)) static inline unsigned
lookup_sequence (databar_segment_t *seg,
                 int fixed,
                 int seq[22])
{
    unsigned n = seg->data / 211, i;
    const unsigned char *p;
    i = (n + 1) / 2 + 1;
    n += 4;
    i = (i * i) / 4;
    dbprintf(2, " {%d,%d:", i, n);
    p = exp_sequences + i;

    fixed >>= 1;
    seq[0] = 0;
    seq[1] = 1;
    for(i = 2; i < n; ) {
        int s = *p;
        if(!(i & 2)) {
            p++;
            s >>= 4;
        }
        else
            s &= 0xf;
        if(s == fixed)
            fixed = -1;
        s <<= 1;
        dbprintf(2, "%x", s);
        seq[i++] = s++;
        seq[i++] = s;
    }
    dbprintf(2, "}");
    seq[n] = -1;
    return(fixed < 1);
}