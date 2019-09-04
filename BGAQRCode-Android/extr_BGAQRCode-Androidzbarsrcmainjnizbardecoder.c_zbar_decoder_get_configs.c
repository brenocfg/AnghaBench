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
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
typedef  int /*<<< orphan*/  zbar_decoder_t ;

/* Variables and functions */
 unsigned int* decoder_get_configp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

unsigned int zbar_decoder_get_configs (const zbar_decoder_t *dcode,
                                       zbar_symbol_type_t sym)
{
    const unsigned *config = decoder_get_configp(dcode, sym);
    if(!config)
        return(0);
    return(*config);
}