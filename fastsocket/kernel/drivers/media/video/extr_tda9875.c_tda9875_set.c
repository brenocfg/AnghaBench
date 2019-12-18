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
struct tda9875 {int lvol; int rvol; int bass; int treble; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDA9875_MBA ; 
 int /*<<< orphan*/  TDA9875_MTR ; 
 int /*<<< orphan*/  TDA9875_MVL ; 
 int /*<<< orphan*/  TDA9875_MVR ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  tda9875_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 
 struct tda9875* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int,int,int) ; 

__attribute__((used)) static void tda9875_set(struct v4l2_subdev *sd)
{
	struct tda9875 *tda = to_state(sd);
	unsigned char a;

	v4l2_dbg(1, debug, sd, "tda9875_set(%04x,%04x,%04x,%04x)\n",
		tda->lvol, tda->rvol, tda->bass, tda->treble);

	a = tda->lvol & 0xff;
	tda9875_write(sd, TDA9875_MVL, a);
	a =tda->rvol & 0xff;
	tda9875_write(sd, TDA9875_MVR, a);
	a =tda->bass & 0xff;
	tda9875_write(sd, TDA9875_MBA, a);
	a =tda->treble  & 0xff;
	tda9875_write(sd, TDA9875_MTR, a);
}