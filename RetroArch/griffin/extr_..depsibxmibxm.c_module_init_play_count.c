#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct module {int sequence_len; int* sequence; int num_patterns; TYPE_1__* patterns; } ;
struct TYPE_2__ {int num_rows; } ;

/* Variables and functions */

__attribute__((used)) static int module_init_play_count( struct module *module, char **play_count ) {
	int idx, pat, rows, len = 0;
	for( idx = 0; idx < module->sequence_len; idx++ ) {
		pat = module->sequence[ idx ];
		rows = ( pat < module->num_patterns ) ? module->patterns[ pat ].num_rows : 0;
		if( play_count ) {
			play_count[ idx ] = play_count[ 0 ] ? &play_count[ 0 ][ len ] : NULL;
		}
		len += rows;
	}
	return len;
}