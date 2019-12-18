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
struct TYPE_2__ {int SampleResolution; int Loop; int Bidirectional; int Reverse; int /*<<< orphan*/  FrequencyBias; int /*<<< orphan*/  sampleEndOffset; int /*<<< orphan*/  loopEndOffset; int /*<<< orphan*/  loopStartOffset; int /*<<< orphan*/  sampleStartOffset; } ;
typedef  TYPE_1__ wavefront_sample ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  demunge_int32 (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,int) ; 

__attribute__((used)) static void
process_sample_hdr (u8 *buf)

{
	wavefront_sample s;
	u8 *ptr;

	ptr = buf;

	/* The board doesn't send us an exact copy of a "wavefront_sample"
	   in response to an Upload Sample Header command. Instead, we 
	   have to convert the data format back into our data structure,
	   just as in the Download Sample command, where we have to do
	   something very similar in the reverse direction.
	*/

	*((u32 *) &s.sampleStartOffset) = demunge_int32 (ptr, 4); ptr += 4;
	*((u32 *) &s.loopStartOffset) = demunge_int32 (ptr, 4); ptr += 4;
	*((u32 *) &s.loopEndOffset) = demunge_int32 (ptr, 4); ptr += 4;
	*((u32 *) &s.sampleEndOffset) = demunge_int32 (ptr, 4); ptr += 4;
	*((u32 *) &s.FrequencyBias) = demunge_int32 (ptr, 3); ptr += 3;

	s.SampleResolution = *ptr & 0x3;
	s.Loop = *ptr & 0x8;
	s.Bidirectional = *ptr & 0x10;
	s.Reverse = *ptr & 0x40;

	/* Now copy it back to where it came from */

	memcpy (buf, (unsigned char *) &s, sizeof (wavefront_sample));
}