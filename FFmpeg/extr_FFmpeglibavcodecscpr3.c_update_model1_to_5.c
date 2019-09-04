#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_5__ {int size; scalar_t__* symbols; int* freqs; int maxpos; int type; scalar_t__ cntsum; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int /*<<< orphan*/  AV_QSORT (scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpbytes ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  uint8_t ; 

__attribute__((used)) static int update_model1_to_5(PixelModel3 *m, uint32_t val)
{
    PixelModel3 n = {0};
    int i, size, freqs;
    uint32_t a;

    size = m->size;
    n.size = size;
    for (i = 0; i < size; i++) {
        n.symbols[i] = m->symbols[i];
    }
    AV_QSORT(n.symbols, size, uint8_t, cmpbytes);
    size = n.size;
    for (i = 0; i < size; i++) {
        if (val == n.symbols[i]) {
            n.freqs[i] = 100;
            n.maxpos = i;
        } else {
            n.freqs[i] = 50;
        }
    }
    a = 256 - size;
    for (i = 0; i < size; i++, a += freqs)
        freqs = n.freqs[i];
    n.type = 5;
    n.cntsum = a;

    memcpy(m, &n, sizeof(n));

    return 0;
}