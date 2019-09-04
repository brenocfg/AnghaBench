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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int tabsize; int bits; scalar_t__ mode; TYPE_1__* tab; } ;
struct TYPE_4__ {int code; int hash_prefix; int /*<<< orphan*/  suffix; } ;
typedef  TYPE_2__ LZWEncodeState ;

/* Variables and functions */
 scalar_t__ FF_LZW_GIF ; 

__attribute__((used)) static inline void addCode(LZWEncodeState * s, uint8_t c, int hash_prefix, int hash_code)
{
    s->tab[hash_code].code = s->tabsize;
    s->tab[hash_code].suffix = c;
    s->tab[hash_code].hash_prefix = hash_prefix;

    s->tabsize++;

    if (s->tabsize >= (1 << s->bits) + (s->mode == FF_LZW_GIF))
        s->bits++;
}