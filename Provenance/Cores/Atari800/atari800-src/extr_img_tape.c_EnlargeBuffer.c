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
typedef  int /*<<< orphan*/  UBYTE ;
struct TYPE_3__ {size_t buffer_size; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ IMG_TAPE_t ;

/* Variables and functions */
 int /*<<< orphan*/  Util_realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void EnlargeBuffer(IMG_TAPE_t *file, size_t size)
{
	if (file->buffer_size < size) {
		/* Enlarge the buffer at least 2 times. */
		file->buffer_size *= 2;
		if (file->buffer_size < size)
			file->buffer_size = size;
		file->buffer = Util_realloc(file->buffer, file->buffer_size * sizeof(UBYTE));
	}
}