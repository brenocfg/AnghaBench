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
struct w8001_coord {int /*<<< orphan*/  tilt_y; int /*<<< orphan*/  tilt_x; int /*<<< orphan*/  pen_pressure; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct w8001 {int /*<<< orphan*/  response; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  W8001_CMD_QUERY ; 
 int /*<<< orphan*/  W8001_CMD_START ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_data (int /*<<< orphan*/ ,struct w8001_coord*) ; 
 int w8001_command (struct w8001*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w8001_setup(struct w8001 *w8001)
{
	struct input_dev *dev = w8001->dev;
	struct w8001_coord coord;
	int error;

	error = w8001_command(w8001, W8001_CMD_QUERY, true);
	if (error)
		return error;

	parse_data(w8001->response, &coord);

	input_set_abs_params(dev, ABS_X, 0, coord.x, 0, 0);
	input_set_abs_params(dev, ABS_Y, 0, coord.y, 0, 0);
	input_set_abs_params(dev, ABS_PRESSURE, 0, coord.pen_pressure, 0, 0);
	input_set_abs_params(dev, ABS_TILT_X, 0, coord.tilt_x, 0, 0);
	input_set_abs_params(dev, ABS_TILT_Y, 0, coord.tilt_y, 0, 0);

	return w8001_command(w8001, W8001_CMD_START, false);
}