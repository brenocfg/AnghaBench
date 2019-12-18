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
struct mtip_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void mtip_null_completion(struct mtip_port *port,
			    int tag,
			    void *data,
			    int status)
{
	return;
}