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
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AACEncContext ;

/* Variables and functions */
 char const FFMIN (int,int) ; 
 char const TYPE_FIL ; 
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,char const) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void put_bitstream_info(AACEncContext *s, const char *name)
{
    int i, namelen, padbits;

    namelen = strlen(name) + 2;
    put_bits(&s->pb, 3, TYPE_FIL);
    put_bits(&s->pb, 4, FFMIN(namelen, 15));
    if (namelen >= 15)
        put_bits(&s->pb, 8, namelen - 14);
    put_bits(&s->pb, 4, 0); //extension type - filler
    padbits = -put_bits_count(&s->pb) & 7;
    avpriv_align_put_bits(&s->pb);
    for (i = 0; i < namelen - 2; i++)
        put_bits(&s->pb, 8, name[i]);
    put_bits(&s->pb, 12 - padbits, 0);
}