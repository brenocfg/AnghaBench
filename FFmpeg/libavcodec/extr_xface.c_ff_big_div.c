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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int nb_words; int* words; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */
 int XFACE_BITSPERWORD ; 
 int XFACE_WORDMASK ; 

void ff_big_div(BigInt *b, uint8_t a, uint8_t *r)
{
    int i;
    uint8_t *w;
    uint16_t c, d;

    a &= XFACE_WORDMASK;
    if (a == 1 || b->nb_words == 0) {
        *r = 0;
        return;
    }

    /* treat this as a == WORDCARRY and just shift everything right a WORD */
    if (a == 0) {
        i = --b->nb_words;
        w = b->words;
        *r = *w;
        while (i--) {
            *w = *(w + 1);
            w++;
        }
        *w = 0;
        return;
    }
    i = b->nb_words;
    w = b->words + i;
    c = 0;
    while (i--) {
        c <<= XFACE_BITSPERWORD;
        c += *--w;
        d = c / (uint16_t)a;
        c = c % (uint16_t)a;
        *w = d & XFACE_WORDMASK;
    }
    *r = c;
    if (b->words[b->nb_words - 1] == 0)
        b->nb_words--;
}