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
typedef  int /*<<< orphan*/  u8 ;
struct wps_credential {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int wps_process_cred_key_prov_auto(struct wps_credential *cred,
					  const u8 *key_prov_auto)
{
	if (key_prov_auto == NULL)
		return 0; /* optional attribute */

	wpa_printf(MSG_DEBUG,  "WPS: Key Provided Automatically: %d",
		   *key_prov_auto);

	return 0;
}