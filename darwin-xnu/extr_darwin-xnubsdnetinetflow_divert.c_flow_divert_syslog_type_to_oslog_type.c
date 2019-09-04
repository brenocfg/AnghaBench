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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
#define  LOG_DEBUG 130 
#define  LOG_ERR 129 
#define  LOG_INFO 128 
 int /*<<< orphan*/  OS_LOG_TYPE_DEBUG ; 
 int /*<<< orphan*/  OS_LOG_TYPE_DEFAULT ; 
 int /*<<< orphan*/  OS_LOG_TYPE_ERROR ; 
 int /*<<< orphan*/  OS_LOG_TYPE_INFO ; 

__attribute__((used)) static inline uint8_t
flow_divert_syslog_type_to_oslog_type(int syslog_type)
{
	switch (syslog_type) {
		case LOG_ERR: return OS_LOG_TYPE_ERROR;
		case LOG_INFO: return OS_LOG_TYPE_INFO;
		case LOG_DEBUG: return OS_LOG_TYPE_DEBUG;
		default: return OS_LOG_TYPE_DEFAULT;
	}
}