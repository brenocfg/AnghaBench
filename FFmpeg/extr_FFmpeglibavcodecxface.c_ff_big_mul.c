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
 int XFACE_MAX_WORDS ; 
 int XFACE_WORDMASK ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

void ff_big_mul(BigInt *b, uint8_t a)
{
    int i;
    uint8_t *w;
    uint16_t c;

    a &= XFACE_WORDMASK;
    if (a == 1 || b->nb_words == 0)
        return;
    if (a == 0) {
        /* treat this as a == WORDCARRY and just shift everything left a WORD */
        av_assert0(b->nb_words < XFACE_MAX_WORDS);
        i = b->nb_words++;
        w = b->words + i;
        while (i--) {
            *w = *(w - 1);
            w--;
        }
        *w = 0;
        return;
    }
    i = b->nb_words;
    w = b->words;
    c = 0;
    while (i--) {
        c += (uint16_t)*w * (uint16_t)a;
        *(w++) = c & XFACE_WORDMASK;
        c >>= XFACE_BITSPERWORD;
    }
    if (c) {
        av_assert0(b->nb_words < XFACE_MAX_WORDS);
        b->nb_words++;
        *w = c & XFACE_WORDMASK;
    }
}