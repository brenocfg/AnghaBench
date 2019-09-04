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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */
 int DCA_SUBBAND_SAMPLES ; 
 int /*<<< orphan*/  dca_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ff_dca_vlc_quant_index ; 

__attribute__((used)) static inline int parse_huffman_codes(DCACoreDecoder *s, int32_t *audio, int abits, int sel)
{
    int i;

    // Extract Huffman codes from the bit stream
    for (i = 0; i < DCA_SUBBAND_SAMPLES; i++)
        audio[i] = dca_get_vlc(&s->gb, &ff_dca_vlc_quant_index[abits - 1], sel);

    return 1;
}