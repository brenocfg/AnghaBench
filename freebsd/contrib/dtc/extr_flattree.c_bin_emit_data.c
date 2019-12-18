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
struct data {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 struct data data_append_data (struct data,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bin_emit_data(void *e, struct data d)
{
	struct data *dtbuf = e;

	*dtbuf = data_append_data(*dtbuf, d.val, d.len);
}