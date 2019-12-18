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
typedef  int uint32_t ;
typedef  scalar_t__ u_short ;
typedef  int u_char ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {size_t byte; int bit; } ;
typedef  TYPE_1__ bitmap_offset_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int NBBY ; 
 scalar_t__ TRUE ; 
 int UCHAR_ALL_ONES ; 
 int UINT32_ALL_ONES ; 
 scalar_t__ USHORT_ALL_ONES ; 
 int bit (int) ; 
 TYPE_1__ bitmap_offset (int) ; 

__attribute__((used)) static uint32_t
bitmap_get(u_char * map, uint32_t start_bit, uint32_t bit_count, 
	   boolean_t * ret_is_set)
{
    uint32_t		count;
    int			i;
    boolean_t		is_set;
    bitmap_offset_t 	start;
    bitmap_offset_t	end;

    start = bitmap_offset(start_bit);
    end = bitmap_offset(start_bit + bit_count);

    is_set = (map[start.byte] & bit(start.bit)) ? TRUE : FALSE;
    count = 0;

    if (start.byte < end.byte) {
	uint32_t n_bytes;

	if (start.bit) { /* try to align to a byte */
	    for (i = start.bit; i < NBBY; i++) {
		boolean_t	this_is_set;

		this_is_set = (map[start.byte] & bit(i)) ? TRUE : FALSE;
		if (this_is_set != is_set) {
		    goto done; /* found bit that was different, we're done */
		}
		count++;
	    }
	    start.bit = 0; /* made it to the next byte */
	    start.byte++;
	    if (start.byte == end.byte)
		goto end; /* no more bytes, check for any leftover bits */
	}
	/* calculate how many bytes are left in the range */
	n_bytes = end.byte - start.byte;

	/* check for 4 bytes of the same bits */
	while (n_bytes >= sizeof(uint32_t)) {
	    uint32_t * valPtr = (uint32_t *)(map + start.byte);
	    if ((is_set && *valPtr == UINT32_ALL_ONES) 
		|| (!is_set && *valPtr == 0)) {
		count += sizeof(*valPtr) * NBBY;
		start.byte += sizeof(*valPtr);
		n_bytes -= sizeof(*valPtr);
	    }
	    else
		break; /* bits differ */

	}
	/* check for 2 bytes of the same bits */
	if (n_bytes >= sizeof(u_short)) {
	    u_short * valPtr = (u_short *)(map + start.byte);
			
	    if ((is_set && *valPtr == USHORT_ALL_ONES) 
		|| (!is_set && (*valPtr == 0))) {
		count += sizeof(*valPtr) * NBBY;
		start.byte += sizeof(*valPtr);
		n_bytes -= sizeof(*valPtr);
	    }
	}

	/* check for 1 byte of the same bits */
	if (n_bytes) { 
	    if ((is_set && map[start.byte] == UCHAR_ALL_ONES) 
		|| (!is_set && map[start.byte] == 0)) {
		count += NBBY;
		start.byte++;
		n_bytes--;
	    }
	    /* we found bits that were different, find the first one */
	    if (n_bytes) { 
		for (i = 0; i < NBBY; i++) {
		    boolean_t	this_is_set;

		    this_is_set = (map[start.byte] & bit(i)) ? TRUE : FALSE;
		    if (this_is_set != is_set) {
			break;
		    }
		    count++;
		}
		goto done;
	    }
	}
    }

 end:
    for (i = start.bit; i < (int)end.bit; i++) {
	boolean_t this_is_set = (map[start.byte] & bit(i)) ? TRUE : FALSE;
	
	if (this_is_set != is_set) {
	    break;
	}
	count++;
    }

 done:
    *ret_is_set = is_set;
    return (count);
}