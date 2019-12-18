#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {size_t table_allocated; int /*<<< orphan*/ * table; } ;
typedef  TYPE_1__ VLC ;

/* Variables and functions */
 int FFMAX (int,int const) ; 
 int /*<<< orphan*/  FFMIN (int,int) ; 
 int /*<<< orphan*/  INIT_VLC_USE_NEW_STATIC ; 
 int MAX_VLC_SIZE ; 
 int /*<<< orphan*/  ff_init_vlc_sparse (TYPE_1__*,int /*<<< orphan*/ ,int,int*,int,int,int*,int,int,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_data ; 
 size_t* table_offs ; 

__attribute__((used)) static void rv34_gen_vlc(const uint8_t *bits, int size, VLC *vlc, const uint8_t *insyms,
                         const int num)
{
    int i;
    int counts[17] = {0}, codes[17];
    uint16_t cw[MAX_VLC_SIZE], syms[MAX_VLC_SIZE];
    uint8_t bits2[MAX_VLC_SIZE];
    int maxbits = 0, realsize = 0;

    for(i = 0; i < size; i++){
        if(bits[i]){
            bits2[realsize] = bits[i];
            syms[realsize] = insyms ? insyms[i] : i;
            realsize++;
            maxbits = FFMAX(maxbits, bits[i]);
            counts[bits[i]]++;
        }
    }

    codes[0] = 0;
    for(i = 0; i < 16; i++)
        codes[i+1] = (codes[i] + counts[i]) << 1;
    for(i = 0; i < realsize; i++)
        cw[i] = codes[bits2[i]]++;

    vlc->table = &table_data[table_offs[num]];
    vlc->table_allocated = table_offs[num + 1] - table_offs[num];
    ff_init_vlc_sparse(vlc, FFMIN(maxbits, 9), realsize,
                       bits2, 1, 1,
                       cw,    2, 2,
                       syms,  2, 2, INIT_VLC_USE_NEW_STATIC);
}