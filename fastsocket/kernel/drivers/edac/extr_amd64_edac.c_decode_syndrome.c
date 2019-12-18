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
typedef  unsigned int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  debugf0 (char*,unsigned int) ; 

__attribute__((used)) static int decode_syndrome(u16 syndrome, u16 *vectors, unsigned num_vecs,
			   unsigned v_dim)
{
	unsigned int i, err_sym;

	for (err_sym = 0; err_sym < num_vecs / v_dim; err_sym++) {
		u16 s = syndrome;
		unsigned v_idx =  err_sym * v_dim;
		unsigned v_end = (err_sym + 1) * v_dim;

		/* walk over all 16 bits of the syndrome */
		for (i = 1; i < (1U << 16); i <<= 1) {

			/* if bit is set in that eigenvector... */
			if (v_idx < v_end && vectors[v_idx] & i) {
				u16 ev_comp = vectors[v_idx++];

				/* ... and bit set in the modified syndrome, */
				if (s & i) {
					/* remove it. */
					s ^= ev_comp;

					if (!s)
						return err_sym;
				}

			} else if (s & i)
				/* can't get to zero, move to next symbol */
				break;
		}
	}

	debugf0("syndrome(%x) not found\n", syndrome);
	return -1;
}