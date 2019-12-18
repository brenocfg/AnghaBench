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
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int wps_process_cred_eap_identity(struct wps_credential *cred,
					 const u8 *identity,
					 size_t identity_len)
{
	if (identity == NULL)
		return 0; /* optional attribute */

	wpa_hexdump_ascii(MSG_DEBUG, "WPS: EAP Identity",
			  identity, identity_len);

	return 0;
}