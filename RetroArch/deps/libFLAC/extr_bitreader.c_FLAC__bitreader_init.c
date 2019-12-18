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
typedef  int /*<<< orphan*/  brword ;
struct TYPE_3__ {int capacity; void* client_data; int /*<<< orphan*/  read_callback; int /*<<< orphan*/ * buffer; scalar_t__ consumed_bits; scalar_t__ consumed_words; scalar_t__ bytes; scalar_t__ words; } ;
typedef  int FLAC__bool ;
typedef  int /*<<< orphan*/  FLAC__BitReaderReadCallback ;
typedef  TYPE_1__ FLAC__BitReader ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 int FLAC__BITREADER_DEFAULT_CAPACITY ; 
 scalar_t__ malloc (int) ; 

FLAC__bool FLAC__bitreader_init(FLAC__BitReader *br, FLAC__BitReaderReadCallback rcb, void *cd)
{
	FLAC__ASSERT(0 != br);

	br->words          = br->bytes = 0;
	br->consumed_words = br->consumed_bits = 0;
	br->capacity       = FLAC__BITREADER_DEFAULT_CAPACITY;
	br->buffer         = (brword*)malloc(sizeof(brword) * br->capacity);
	if(br->buffer == 0)
		return false;
	br->read_callback = rcb;
	br->client_data = cd;

	return true;
}