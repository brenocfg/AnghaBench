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
struct pattern {int num_channels; int num_rows; int /*<<< orphan*/ * data; } ;
struct note {int /*<<< orphan*/  param; int /*<<< orphan*/  effect; int /*<<< orphan*/  volume; int /*<<< orphan*/  instrument; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct note*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pattern_get_note( struct pattern *pattern, int row, int chan, struct note *dest ) {
	int offset = ( row * pattern->num_channels + chan ) * 5;
	if( offset >= 0 && row < pattern->num_rows && chan < pattern->num_channels ) {
		dest->key = pattern->data[ offset ];
		dest->instrument = pattern->data[ offset + 1 ];
		dest->volume = pattern->data[ offset + 2 ];
		dest->effect = pattern->data[ offset + 3 ];
		dest->param = pattern->data[ offset + 4 ];
	} else {
		memset( dest, 0, sizeof( struct note ) );
	}
}