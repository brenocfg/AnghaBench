#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void fill_random(uint8_t *tab, int size)
{
    int i;
    AVLFG prng;

    av_lfg_init(&prng, 1);
    for(i=0;i<size;i++) {
        tab[i] = av_lfg_get(&prng) % 256;
    }
}