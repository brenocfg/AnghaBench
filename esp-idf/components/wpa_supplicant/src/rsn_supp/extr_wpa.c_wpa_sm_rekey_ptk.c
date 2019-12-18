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
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_sm_key_request (struct wpa_sm*,int /*<<< orphan*/ ,int) ; 

void   wpa_sm_rekey_ptk(void *eloop_ctx, void *timeout_ctx)
{
    struct wpa_sm *sm = eloop_ctx;

   #ifdef DEBUG_PRINT    
    wpa_printf(MSG_DEBUG, "WPA: Request PTK rekeying");
   #endif
    wpa_sm_key_request(sm, 0, 1);
}