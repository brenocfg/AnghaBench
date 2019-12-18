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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct bitstream {int /*<<< orphan*/  dlength; scalar_t__ doffset; int /*<<< orphan*/  const* read; scalar_t__ bits; scalar_t__ buffer; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

struct bitstream* create_bitstream(const void *src, uint32_t srclength)
{
	struct bitstream* bitstream = (struct bitstream*)malloc(sizeof(struct bitstream));
	bitstream->buffer = 0;
	bitstream->bits = 0;
	bitstream->read = (const uint8_t*)src;
	bitstream->doffset = 0;
	bitstream->dlength = srclength;
	return bitstream;
}