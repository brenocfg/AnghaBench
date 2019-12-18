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
struct hpsb_protocol_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int __hpsb_register_protocol (struct hpsb_protocol_driver*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hpsb_register_protocol(struct hpsb_protocol_driver *driver)
{
	return __hpsb_register_protocol(driver, THIS_MODULE);
}