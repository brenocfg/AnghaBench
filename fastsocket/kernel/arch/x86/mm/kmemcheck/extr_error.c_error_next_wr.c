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
struct kmemcheck_error {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct kmemcheck_error*) ; 
 size_t error_count ; 
 struct kmemcheck_error* error_fifo ; 
 int /*<<< orphan*/  error_missed_count ; 
 size_t error_wr ; 

__attribute__((used)) static struct kmemcheck_error *error_next_wr(void)
{
	struct kmemcheck_error *e;

	if (error_count == ARRAY_SIZE(error_fifo)) {
		++error_missed_count;
		return NULL;
	}

	e = &error_fifo[error_wr];
	if (++error_wr == ARRAY_SIZE(error_fifo))
		error_wr = 0;
	++error_count;
	return e;
}