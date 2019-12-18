#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num; TYPE_1__* table; } ;
typedef  TYPE_2__ huf_table ;
typedef  int /*<<< orphan*/  bit_stream ;
struct TYPE_4__ {int codelen; int value; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int bit_read (int /*<<< orphan*/ *,int,int,unsigned char**) ; 
 int /*<<< orphan*/  mirror (unsigned long,int) ; 

__attribute__((used)) static void read_huftable (huf_table *h, bit_stream *bs, unsigned char **p) {
    int i, j, k, num;
    int leaflen[32];
    int leafmax;
    unsigned long codeb;	       /* big-endian form of code */

    num = bit_read (bs, 0x1F, 5, p);
    if (!num)
	return;

    leafmax = 1;
    for (i=0; i<num; i++) {
	leaflen[i] = bit_read (bs, 0x0F, 4, p);
	if (leafmax < leaflen[i])
	    leafmax = leaflen[i];
    }

    codeb = 0L;
    k = 0;
    for (i=1; i<=leafmax; i++) {
	for (j=0; j<num; j++)
	    if (leaflen[j] == i) {
		h->table[k].code = mirror (codeb, i);
		h->table[k].codelen = i;
		h->table[k].value = j;
		codeb++;
		k++;
	    }
	codeb <<= 1;
    }

    h->num = k;
}