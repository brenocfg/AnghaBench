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
struct TYPE_3__ {size_t zeroth_band; size_t* bands; scalar_t__ next_band; } ;
typedef  TYPE_1__ shadow_map_t ;
typedef  scalar_t__ boolean_t ;
typedef  size_t band_number_t ;

/* Variables and functions */
 size_t BAND_ZERO ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static boolean_t
shadow_map_mapped_band(shadow_map_t * map, band_number_t band,
		       boolean_t map_it, band_number_t * mapped_band)
{
    boolean_t		is_mapped = FALSE;

    if (band == map->zeroth_band) {
	*mapped_band = BAND_ZERO;
	is_mapped = TRUE;
    }
    else {
	*mapped_band = map->bands[band];
	if (*mapped_band == BAND_ZERO) {
	    if (map_it) {
		/* grow the file */
		if (map->next_band == 0) {
		    /* remember the zero'th band */
		    map->zeroth_band = band;
		}
		*mapped_band = map->bands[band] = map->next_band++;
		is_mapped = TRUE;
	    }
	}
	else {
	    is_mapped = TRUE;
	}
    }
    return (is_mapped);
}