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

/* Variables and functions */
#define  CPER_SEV_CORRECTED 131 
#define  CPER_SEV_FATAL 130 
#define  CPER_SEV_INFORMATIONAL 129 
#define  CPER_SEV_RECOVERABLE 128 
 int GHES_SEV_CORRECTED ; 
 int GHES_SEV_NO ; 
 int GHES_SEV_PANIC ; 
 int GHES_SEV_RECOVERABLE ; 

__attribute__((used)) static inline int ghes_severity(int severity)
{
	switch (severity) {
	case CPER_SEV_INFORMATIONAL:
		return GHES_SEV_NO;
	case CPER_SEV_CORRECTED:
		return GHES_SEV_CORRECTED;
	case CPER_SEV_RECOVERABLE:
		return GHES_SEV_RECOVERABLE;
	case CPER_SEV_FATAL:
		return GHES_SEV_PANIC;
	default:
		/* Unkown, go panic */
		return GHES_SEV_PANIC;
	}
}