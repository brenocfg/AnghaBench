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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ TLS_VERSION_1 ; 
 scalar_t__ TLS_VERSION_1_1 ; 
 scalar_t__ TLS_VERSION_1_2 ; 

int tls_version_ok(u16 ver)
{
	if (ver == TLS_VERSION_1)
		return 1;
#ifdef CONFIG_TLSV11
	if (ver == TLS_VERSION_1_1)
		return 1;
#endif /* CONFIG_TLSV11 */
#ifdef CONFIG_TLSV12
	if (ver == TLS_VERSION_1_2)
		return 1;
#endif /* CONFIG_TLSV12 */

	return 0;
}