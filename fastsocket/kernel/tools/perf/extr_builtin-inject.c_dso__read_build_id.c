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
struct dso {int has_build_id; int /*<<< orphan*/  build_id; int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 scalar_t__ filename__read_build_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dso__read_build_id(struct dso *self)
{
	if (self->has_build_id)
		return 0;

	if (filename__read_build_id(self->long_name, self->build_id,
				    sizeof(self->build_id)) > 0) {
		self->has_build_id = true;
		return 0;
	}

	return -1;
}