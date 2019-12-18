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
struct format {int /*<<< orphan*/  fields; int /*<<< orphan*/  common_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_format_fields (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_formats(struct format *format)
{
	free_format_fields(format->common_fields);
	free_format_fields(format->fields);
}