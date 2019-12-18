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
struct v4l2_subdev {int dummy; } ;
struct saa7110 {int input; } ;

/* Variables and functions */
#define  FRESP_06H_COMPST 129 
#define  FRESP_06H_SVIDEO 128 
 int /*<<< orphan*/  saa7110_write (struct v4l2_subdev*,int,unsigned char const) ; 
 struct saa7110* to_saa7110 (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7110_selmux(struct v4l2_subdev *sd, int chan)
{
	static const unsigned char modes[9][8] = {
		/* mode 0 */
		{FRESP_06H_COMPST, 0xD9, 0x17, 0x40, 0x03,
			      0x44, 0x75, 0x16},
		/* mode 1 */
		{FRESP_06H_COMPST, 0xD8, 0x17, 0x40, 0x03,
			      0x44, 0x75, 0x16},
		/* mode 2 */
		{FRESP_06H_COMPST, 0xBA, 0x07, 0x91, 0x03,
			      0x60, 0xB5, 0x05},
		/* mode 3 */
		{FRESP_06H_COMPST, 0xB8, 0x07, 0x91, 0x03,
			      0x60, 0xB5, 0x05},
		/* mode 4 */
		{FRESP_06H_COMPST, 0x7C, 0x07, 0xD2, 0x83,
			      0x60, 0xB5, 0x03},
		/* mode 5 */
		{FRESP_06H_COMPST, 0x78, 0x07, 0xD2, 0x83,
			      0x60, 0xB5, 0x03},
		/* mode 6 */
		{FRESP_06H_SVIDEO, 0x59, 0x17, 0x42, 0xA3,
			      0x44, 0x75, 0x12},
		/* mode 7 */
		{FRESP_06H_SVIDEO, 0x9A, 0x17, 0xB1, 0x13,
			      0x60, 0xB5, 0x14},
		/* mode 8 */
		{FRESP_06H_SVIDEO, 0x3C, 0x27, 0xC1, 0x23,
			      0x44, 0x75, 0x21}
	};
	struct saa7110 *decoder = to_saa7110(sd);
	const unsigned char *ptr = modes[chan];

	saa7110_write(sd, 0x06, ptr[0]);	/* Luminance control    */
	saa7110_write(sd, 0x20, ptr[1]);	/* Analog Control #1    */
	saa7110_write(sd, 0x21, ptr[2]);	/* Analog Control #2    */
	saa7110_write(sd, 0x22, ptr[3]);	/* Mixer Control #1     */
	saa7110_write(sd, 0x2C, ptr[4]);	/* Mixer Control #2     */
	saa7110_write(sd, 0x30, ptr[5]);	/* ADCs gain control    */
	saa7110_write(sd, 0x31, ptr[6]);	/* Mixer Control #3     */
	saa7110_write(sd, 0x21, ptr[7]);	/* Analog Control #2    */
	decoder->input = chan;

	return 0;
}