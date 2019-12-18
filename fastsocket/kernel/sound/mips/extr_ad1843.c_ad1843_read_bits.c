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
struct snd_ad1843 {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  chip; } ;
struct ad1843_bitfield {int lo_bit; int nbits; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad1843_read_bits(struct snd_ad1843 *ad1843,
			    const struct ad1843_bitfield *field)
{
	int w;

	w = ad1843->read(ad1843->chip, field->reg);
	return w >> field->lo_bit & ((1 << field->nbits) - 1);
}