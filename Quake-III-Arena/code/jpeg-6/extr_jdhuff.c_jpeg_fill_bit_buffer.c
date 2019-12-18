#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ boolean ;
struct TYPE_8__ {size_t bytes_in_buffer; int unread_marker; int get_buffer; int bits_left; int /*<<< orphan*/  const* next_input_byte; scalar_t__* printed_eod_ptr; TYPE_3__* cinfo; } ;
typedef  TYPE_2__ bitread_working_state ;
typedef  int bit_buf_type ;
struct TYPE_9__ {TYPE_1__* src; } ;
struct TYPE_7__ {size_t bytes_in_buffer; int /*<<< orphan*/  const* next_input_byte; int /*<<< orphan*/  (* fill_input_buffer ) (TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  const JOCTET ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int GETJOCTET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JWRN_HIT_MARKER ; 
 int MIN_GET_BITS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARNMS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

boolean
jpeg_fill_bit_buffer (bitread_working_state * state,
		      register bit_buf_type get_buffer, register int bits_left,
		      int nbits)
/* Load up the bit buffer to a depth of at least nbits */
{
  /* Copy heavily used state fields into locals (hopefully registers) */
  register const JOCTET * next_input_byte = state->next_input_byte;
  register size_t bytes_in_buffer = state->bytes_in_buffer;
  register int c;

  /* Attempt to load at least MIN_GET_BITS bits into get_buffer. */
  /* (It is assumed that no request will be for more than that many bits.) */

  while (bits_left < MIN_GET_BITS) {
    /* Attempt to read a byte */
    if (state->unread_marker != 0)
      goto no_more_data;	/* can't advance past a marker */

    if (bytes_in_buffer == 0) {
      if (! (*state->cinfo->src->fill_input_buffer) (state->cinfo))
	return FALSE;
      next_input_byte = state->cinfo->src->next_input_byte;
      bytes_in_buffer = state->cinfo->src->bytes_in_buffer;
    }
    bytes_in_buffer--;
    c = GETJOCTET(*next_input_byte++);

    /* If it's 0xFF, check and discard stuffed zero byte */
    if (c == 0xFF) {
      do {
	if (bytes_in_buffer == 0) {
	  if (! (*state->cinfo->src->fill_input_buffer) (state->cinfo))
	    return FALSE;
	  next_input_byte = state->cinfo->src->next_input_byte;
	  bytes_in_buffer = state->cinfo->src->bytes_in_buffer;
	}
	bytes_in_buffer--;
	c = GETJOCTET(*next_input_byte++);
      } while (c == 0xFF);

      if (c == 0) {
	/* Found FF/00, which represents an FF data byte */
	c = 0xFF;
      } else {
	/* Oops, it's actually a marker indicating end of compressed data. */
	/* Better put it back for use later */
	state->unread_marker = c;

      no_more_data:
	/* There should be enough bits still left in the data segment; */
	/* if so, just break out of the outer while loop. */
	if (bits_left >= nbits)
	  break;
	/* Uh-oh.  Report corrupted data to user and stuff zeroes into
	 * the data stream, so that we can produce some kind of image.
	 * Note that this code will be repeated for each byte demanded
	 * for the rest of the segment.  We use a nonvolatile flag to ensure
	 * that only one warning message appears.
	 */
	if (! *(state->printed_eod_ptr)) {
	  WARNMS(state->cinfo, JWRN_HIT_MARKER);
	  *(state->printed_eod_ptr) = TRUE;
	}
	c = 0;			/* insert a zero byte into bit buffer */
      }
    }

    /* OK, load c into get_buffer */
    get_buffer = (get_buffer << 8) | c;
    bits_left += 8;
  }

  /* Unload the local registers */
  state->next_input_byte = next_input_byte;
  state->bytes_in_buffer = bytes_in_buffer;
  state->get_buffer = get_buffer;
  state->bits_left = bits_left;

  return TRUE;
}