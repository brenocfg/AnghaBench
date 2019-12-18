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
struct TYPE_3__ {int day; int month; int year; } ;
typedef  TYPE_1__ network_mysqld_type_date_t ;
typedef  int gboolean ;

/* Variables and functions */

__attribute__((used)) static gboolean network_mysqld_type_date_date_is_valid(network_mysqld_type_date_t *date) {
	return (date->day <= 31 &&
	      date->month <= 12 &&
	      date->year  <= 9999);
}