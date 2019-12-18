#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  days; scalar_t__ sign; } ;
typedef  TYPE_1__ network_mysqld_type_time_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ network_mysqld_type_t ;
typedef  int /*<<< orphan*/  gsize ;

/* Variables and functions */
 int /*<<< orphan*/  NETWORK_MYSQLD_TYPE_TIME_MIN_BUF_LEN ; 
 int /*<<< orphan*/  g_snprintf (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int network_mysqld_type_data_time_get_string(network_mysqld_type_t *type, char **dst, gsize *dst_len) {
	network_mysqld_type_time_t *src = type->data;

	if (NULL == type->data) return -1;

	if (NULL != *dst) {
		/* dst_len already contains a size and we don't have to alloc */
		if (*dst_len < NETWORK_MYSQLD_TYPE_TIME_MIN_BUF_LEN) {
			return -1; /* ... but it is too small .. we could return the right size here */
		}
		*dst_len = g_snprintf(*dst, *dst_len, "%s%d %02u:%02u:%02u.%09u",
				src->sign ? "-" : "",
				src->days,
				src->hour,
				src->min,
				src->sec,
				src->nsec);
	} else {
		*dst = g_strdup_printf("%s%d %02u:%02u:%02u.%09u",
				src->sign ? "-" : "",
				src->days,
				src->hour,
				src->min,
				src->sec,
				src->nsec);
		*dst_len = strlen(*dst);
	}

	return 0;
}