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
struct TYPE_3__ {int* words; int nb_words; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */
 int XFACE_BITSPERWORD ; 
 int XFACE_MAX_WORDS ; 
 int XFACE_WORDMASK ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

void ff_big_add(BigInt *b, uint8_t a)
{
    int i;
    uint8_t *w;
    uint16_t c;

    a &= XFACE_WORDMASK;
    if (a == 0)
        return;
    w = b->words;
    c = a;
    for (i = 0; i < b->nb_words && c; i++) {
        c += *w;
        *w++ = c & XFACE_WORDMASK;
        c >>= XFACE_BITSPERWORD;
    }
    if (i == b->nb_words && c) {
        av_assert0(b->nb_words < XFACE_MAX_WORDS);
        b->nb_words++;
        *w = c & XFACE_WORDMASK;
    }
}