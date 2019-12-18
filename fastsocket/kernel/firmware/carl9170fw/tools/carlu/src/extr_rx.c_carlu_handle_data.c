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
struct carlu {int /*<<< orphan*/  (* rx_cb ) (struct carlu*,void*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,char*,void*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct carlu*,void*,unsigned int) ; 

__attribute__((used)) static void carlu_handle_data(struct carlu *ar, void *buf,
			       unsigned int len)
{
	if (ar->rx_cb) {
		ar->rx_cb(ar, buf, len);
	} else {
		dbg("unhandled data:\n");
		print_hex_dump_bytes(VERBOSE, "DATA:", buf, len);
	}
}