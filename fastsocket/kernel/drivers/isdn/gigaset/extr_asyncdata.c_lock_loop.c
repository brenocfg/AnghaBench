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
struct inbuf_t {struct cardstate* cs; } ;
struct cardstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKCMD ; 
 int /*<<< orphan*/  gigaset_dbg_buffer (int /*<<< orphan*/ ,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  gigaset_if_receive (struct cardstate*,unsigned char*,int) ; 

__attribute__((used)) static inline int lock_loop(unsigned char *src, int numbytes,
			    struct inbuf_t *inbuf)
{
	struct cardstate *cs = inbuf->cs;

	gigaset_dbg_buffer(DEBUG_LOCKCMD, "received response",
			   numbytes, src);
	gigaset_if_receive(cs, src, numbytes);

	return numbytes;
}