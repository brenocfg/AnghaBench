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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct tvp5150 {int /*<<< orphan*/  norm; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  bright; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_BRIGHT_CTL ; 
 int /*<<< orphan*/  TVP5150_CONTRAST_CTL ; 
 int /*<<< orphan*/  TVP5150_HUE_CTL ; 
 int /*<<< orphan*/  TVP5150_SATURATION_CTL ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_init_default ; 
 int /*<<< orphan*/  tvp5150_init_enable ; 
 int /*<<< orphan*/  tvp5150_selmux (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_set_std (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp5150_vdp_init (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp5150_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp5150_write_inittab (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbi_ram_default ; 

__attribute__((used)) static int tvp5150_reset(struct v4l2_subdev *sd, u32 val)
{
	struct tvp5150 *decoder = to_tvp5150(sd);

	/* Initializes TVP5150 to its default values */
	tvp5150_write_inittab(sd, tvp5150_init_default);

	/* Initializes VDP registers */
	tvp5150_vdp_init(sd, vbi_ram_default);

	/* Selects decoder input */
	tvp5150_selmux(sd);

	/* Initializes TVP5150 to stream enabled values */
	tvp5150_write_inittab(sd, tvp5150_init_enable);

	/* Initialize image preferences */
	tvp5150_write(sd, TVP5150_BRIGHT_CTL, decoder->bright);
	tvp5150_write(sd, TVP5150_CONTRAST_CTL, decoder->contrast);
	tvp5150_write(sd, TVP5150_SATURATION_CTL, decoder->contrast);
	tvp5150_write(sd, TVP5150_HUE_CTL, decoder->hue);

	tvp5150_set_std(sd, decoder->norm);
	return 0;
}