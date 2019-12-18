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
struct embedded_panic_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_BUF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* debug_buf_base ; 
 char* debug_buf_ptr ; 
 scalar_t__ debug_buf_size ; 
 scalar_t__ gPanicBase ; 
 scalar_t__ gPanicSize ; 
 int /*<<< orphan*/  panic_info ; 
 int /*<<< orphan*/  printf (char*) ; 

void
debug_log_init(void)
{
#if CONFIG_EMBEDDED
	if (!gPanicBase) {
		printf("debug_log_init: Error!! gPanicBase is still not initialized\n");
		return;
	}
	/* Shift debug buf start location and size by the length of the panic header */
	debug_buf_base = (char *)gPanicBase + sizeof(struct embedded_panic_header);
	debug_buf_ptr = debug_buf_base;
	debug_buf_size = gPanicSize - sizeof(struct embedded_panic_header);
#else
	bzero(panic_info, DEBUG_BUF_SIZE);

	assert(debug_buf_base != NULL);
	assert(debug_buf_ptr != NULL);
	assert(debug_buf_size != 0);
#endif
}