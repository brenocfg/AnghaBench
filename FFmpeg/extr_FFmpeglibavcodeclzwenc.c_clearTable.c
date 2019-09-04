#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bits; int tabsize; TYPE_1__* tab; int /*<<< orphan*/  clear_code; } ;
struct TYPE_5__ {int code; int suffix; int /*<<< orphan*/  hash_prefix; } ;
typedef  TYPE_2__ LZWEncodeState ;

/* Variables and functions */
 int LZW_HASH_SIZE ; 
 int /*<<< orphan*/  LZW_PREFIX_EMPTY ; 
 int /*<<< orphan*/  LZW_PREFIX_FREE ; 
 int hash (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeCode (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clearTable(LZWEncodeState * s)
{
    int i, h;

    writeCode(s, s->clear_code);
    s->bits = 9;
    for (i = 0; i < LZW_HASH_SIZE; i++) {
        s->tab[i].hash_prefix = LZW_PREFIX_FREE;
    }
    for (i = 0; i < 256; i++) {
        h = hash(0, i);
        s->tab[h].code = i;
        s->tab[h].suffix = i;
        s->tab[h].hash_prefix = LZW_PREFIX_EMPTY;
    }
    s->tabsize = 258;
}